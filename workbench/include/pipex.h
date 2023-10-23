#ifndef PIPEX_H
# define PIPEX_H

# define READ_END 0
# define WRITE_END 1
# define MAX_PATH_LENGHT 4096
# define ERROR_MESSAGE "custom err_message with printf template"

# include <unistd.h> /* close, read, write, access, dup, dup2, exit, pipe, execve */
# include <fcntl.h> /* open, unlink */
# include <stdlib.h> /* malloc, free */
# include <stdio.h> /* perror */
# include <string.h> /* strerror */
# include <sys/types.h> /* fork, wait, waitpid */
# include <sys/wait.h> /* wait, waitpid */
# include "../libft/includes/libft.h"

typedef struct	s_errctl
{
	int exit;
	int	argc;
	int	pipe;
	int	fork;
}				t_errctl;

typedef struct	s_bodyctl
{
	char		*rawpath;
	char		**paths;
	t_errctl	errctl;
}				t_bodyctl;

/* **************************************** */

/* main */
//char	*strint	main(int argc, char **argv);
char	*get_path(const char **env); //strncmp until compare == 0 and while *env

/* handle */
char	*err_handle(t_errctl *errctl, int *errvalue, const char *msg);

/* utils */

#endif
