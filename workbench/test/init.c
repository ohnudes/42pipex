#include "test.h"

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
			//print_vec(pdata->paths, "init_paths/paths");
			pdata->rawcmd[0] = ft_split(av[2], ' ');
			//print_vec(pdata->rawcmd[0], "init_paths/rawcmd[0]");
			if (pdata->rawcmd[0])
			{
				pdata->rawcmd[1] = ft_split(av[3], ' ');
				//print_vec(pdata->rawcmd[1], "init_paths/rawcmd[1]");
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
			perror("cmd_check check");
			j++;
			if (j == 2)
			{
				return (0);
			}
			i = 0;
		}
		else
			free(pathdata->cmd_path[j]);
	}
	return (-1);
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
