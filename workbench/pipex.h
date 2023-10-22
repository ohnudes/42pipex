#ifndef PIPEX_H
# define PIPEX_H

# define READ_END 0
# define WRITE_END 1
# define MAX_PATH_LENGHT 4096
# define ERROR_MESSAGE "custom err_message with printf template"

# include <unistd.h> /* open, close, read, write, access, dup, dup2, exit, pipe, unlink, execve */
# include <stdlib.h> /* malloc, free */
# include <stdio.h> /* perror */
# include <string.h> /* strerror */
# include <sys/types.h> /* fork, wait, waitpid */
# include <sys/wait.h> /* wait, waitpid */

typedef struct	s_errctl
{
	int	pipe;
	int	fork;
}				t_errctl;

typedef struct	s_bodyctl
{
	char		*pathdata;
	t_errctl	errctl;
}				t_bodyctl;

/* **************************************** */

/* main */
//char	*strint	main(int argc, char **argv);
char	*get_path(const char *cmd, t_errctl *errctl);

/* parse cmds
 * parse 
 *
 */

/* utils */

#endif
