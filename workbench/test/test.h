
#ifndef TEST_H
# define TEST_H

# include <unistd.h> /* close, read, write, access, dup, dup2, exit, pipe, execve */
# include <fcntl.h> /* open, unlink */
# include <stdlib.h> /* malloc, free */
# include <stdio.h> /* perror */
# include <string.h> /* strerror */
# include <sys/types.h> /* fork, wait, waitpid */
# include <sys/wait.h> /* wait, waitpid */
# include "../libft/includes/libft.h"

# define READ_END 0
# define WRITE_END 1

typedef struct	data_s
{
	size_t	path_len;
	char	**paths;
	char	**rawcmd[2];
	char	*cmd_path[2];
}				data_t;

typedef struct	pipecon_s
{
	int		ft[2];
	int		fd[2];
}				pipecon_t;

typedef enum	e_exitcode
{
	initpath,
	cmdcheck,
	initpipe_values,
	end,
}				t_exitcode;

/* init, in order of execution */
int		init_path(data_t *data, char **av, char **env);
int		cmd_check(data_t *pipex, char **rawcmd[2]);
int		init_pipe_values(pipecon_t *pipe, int argc, char **argv);

/* print util */
void	print_vec(char	**str, char *msg);

/* utils */
void	free_vec(char **str);
void	exit_mem(data_t *pdata);
void	exit_fd(pipecon_t *pipes);
int		exit_ctl(data_t *pathdata, pipecon_t *pipes, int code);

#endif
