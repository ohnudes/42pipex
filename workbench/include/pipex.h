#ifndef PIPEX_H
# define PIPEX_H

# define READ_END 0
# define WRITE_END 1
# define MAX_PATH_LENGHT 4096

# include <unistd.h> /* close, read, write, access, dup, dup2, exit, pipe, execve */
# include <fcntl.h> /* open, unlink */
# include <stdlib.h> /* malloc, free */
# include <stdio.h> /* perror */
# include <string.h> /* strerror */
# include <sys/types.h> /* fork, wait, waitpid */
# include <sys/wait.h> /* wait, waitpid */
# include "../libft/includes/libft.h"

typedef struct	s_fdbridge
{
	int		ft1;
	int		ft2;
	int		fd[2];
}				t_fdbridge;

typedef struct	s_pathdata
{
	char	**paths;
	char	**cmd1path;
	char	**cmd2path;
	char	**rawcmd1;
	char	**rawcmd2;
}				t_pathdata;

typedef struct	s_pipex
{
	t_pathdata	pathdata;
	t_fdbridge	connection;
}				t_pipex;

/* **************************************** */

/* main */
void	body(t_pipex *pipex, char *env[]);
void	child_labour(t_pipex *pipex);
void	end_pipex(t_pipex *pipex);

/* handle */
void	init_path(t_pathdata *pipex, char **av, char **env);
void	init_fd(t_fdbridge *pipex, char **av);
void	cmd_check(t_pathdata *pipex, char ***rawcmd, char *av[]);

/* utils */
char	*get_path(char **env);
char	**free_dchar(char **ptr);
int		err_msg(char *msg);

#endif
