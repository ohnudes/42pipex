
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

typedef struct	data_s
{
	size_t	path_len;
	char	**paths;
	char	**rawcmd[2];
	char	*cmd_path[2];
}				data_t;

//init
void	init_path(data_t *data, char **av, char **env);
void	cmd_check(data_t *pipex, char **rawcmd[2]);

//print
void	print_vec(char	**str, char *msg);

// utils
void	free_vec(char **str);
void	exit_mem(data_t *pdata);

#endif
