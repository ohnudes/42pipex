
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "../libft/includes/libft.h"

typedef struct	pipecon_s
{
	int		ft[2];
	int		fd[2];
}				pipecon_t;

typedef struct	data_s
{
	size_t	path_len;
	char	**paths;
	char	**rawcmd[2];
	char	*cmd_path[2];
}				data_t;

void	print_vec(char	**str, char *msg)
{
	size_t	i;
	i = 0;
	while (str[i] && str + i + 1)
	{
		printf("%s	%p	%s\n\n", msg, str, str[i]);
		i++;
	}
}

void	free_vec(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	while (i)
	{
		i--;
		free(str[i]);
	}
	free(str);
}

void	exit_mem(data_t *pdata)
{
	size_t	i;

	i = 0;
	if (pdata->paths)
	{
		free_vec(pdata->paths);
		pdata->paths = NULL;
	}
	while (i < 2)
	{
		if (pdata->rawcmd[i])
		{
			free_vec(pdata->rawcmd[i]);
			pdata->rawcmd[i] = NULL;
		}
		if (pdata->cmd_path[i])
		{
			free(pdata->cmd_path[i]);
			pdata->cmd_path[i] = NULL;
		}
		i++;
	}
}


static char	*get_path(char **env)
{
	while (ft_strncmp("PATH", *env, 4) && *env)
		env++;
	return (*env + 5);
}

static char	**fill_paths(char *raw, char **vector, size_t *path_len)
{
	char	*swp;
	size_t	i;
	size_t	j;
	
	i = 0;
	j = 0;
	vector = ft_split(raw, ':');
	if (!vector)
		return (NULL);
	while (vector[i])
	{
		swp = vector[i];
		j = ft_strlen(swp);
		if (swp[j - 1] != '/')
		{
			vector[i] = ft_strjoin(vector[i], "/");
			free(swp);
		}
		i++;
	}
	*path_len = i;
	return (vector);
}

int	init_path(data_t *pdata, char **av, char **env)
{
	char	*tmp;
	tmp = get_path(env);
	if (tmp)
	{
		pdata->paths = fill_paths(tmp, pdata->paths, &pdata->path_len);
		if (pdata->paths)
		{
			pdata->rawcmd[0] = ft_split(av[2], ' ');
			print_vec(pdata->rawcmd[0], "init_paths/rawcmd[0]");
			if (pdata->rawcmd[0])
			{
				pdata->rawcmd[1] = ft_split(av[3], ' ');
				print_vec(pdata->rawcmd[1], "init_paths/rawcmd[1]");
				return (0);
			}
		}
	}
	exit_mem(pdata);
	return (-1);
}

int	cmd_check(data_t *pathdata, char **rawcmd[2])
{
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	while (++i < pathdata->path_len)
	{
		pathdata->cmd_path[j] = ft_strjoin(pathdata->paths[i], *rawcmd[j]);
		if (access(pathdata->cmd_path[j], 0) == 0)
		{
			j++;
			if (j == 2)
				break ;
			i = 0;
		}
		else
		{
			free(pathdata->cmd_path[j]);
			if (i + 1 == pathdata->path_len)
			{
				perror("cmd not valid");
				return (-1);
			}
		}
	}
	errno = 0;
	return (0);
}

int	init_pipe_values(pipecon_t *pipe, char **argv)
{
	pipe->ft[0] = open(argv[1], O_RDONLY);
	if (pipe->ft[0] == -1)
	{
		perror("init_pipe_values/inline: not valid");
		return (-1);
	}
	pipe->ft[1] = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (pipe->ft[1] == -1)
	{
		close(pipe->ft[0]);
		perror("init_pipe_values/outline: error");
		return (-1);
	}
	return (0);
}

int	main(int ac, char **av, char *env[])
{
	data_t		pathdt;
	pipecon_t	pipex;
	int			pid;
	int			pid2;

	pathdt = (data_t){};
	pipex = (pipecon_t){};
	init_path(&pathdt, av, env);
	cmd_check(&pathdt, pathdt.rawcmd);
	perror("check");
	init_pipe_values(&pipex, av);
	printf("cmd_path[0]	%p	%s\n", pathdt.cmd_path[0], pathdt.cmd_path[0]);
	printf("cmd_path[1]	%p	%s\n", pathdt.cmd_path[1], pathdt.cmd_path[1]);
	pipe(pipex.fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(pipex.fd[1], STDOUT_FILENO);
		dup2(pipex.ft[0], 0);
		close(pipex.fd[0]);
		close(pipex.fd[1]);
		execve(pathdt.cmd_path[0], pathdt.rawcmd[0], env);
		exit(0);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(pipex.fd[0], STDIN_FILENO);
		dup2(pipex.ft[1], STDOUT_FILENO);
		close(pipex.fd[1]);
		close(pipex.fd[0]);
		execve(pathdt.cmd_path[1], pathdt.rawcmd[1], env);
		exit(0);
	}
	close(pipex.fd[0]);
	close(pipex.fd[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	exit_mem(&pathdt);
	return (0);
}
