/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaturan <nmaturan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:46:58 by nmaturan          #+#    #+#             */
/*   Updated: 2023/11/06 13:22:19 by nmaturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* close, read, write, access, dup, dup2, exit, pipe, execve */
# include <unistd.h>
# include <fcntl.h> /* open, unlink */
# include <stdlib.h> /* malloc, free */
# include <stdio.h> /* perror */
# include <string.h> /* strerror */
# include <sys/types.h> /* fork, wait, waitpid */
# include <sys/wait.h> /* wait, waitpid */
# include <errno.h>
# include "../libft/includes/libft.h"

# define READ_END 0
# define WRITE_END 1

typedef struct data_s
{
	size_t	path_len;
	char	**paths;
	char	**rawcmd[2];
	char	*cmd_path[2];
}				data_t;

typedef struct pipecon_s
{
	int		ft[2];
	int		fd[2];
}			pipecon_t;

/* init, in order of execution */
int		init_path(data_t *data, char **av, char **env);
int		cmd_check(data_t *pipex, char **rawcmd[2]);
int		init_pipe_values(pipecon_t *pipe, char **argv);

/* print util */
void	print_vec(char	**str, char *msg);

/* utils */
void	exit_mem(data_t *pdata);
void	exit_pipes(pipecon_t *pipes);
int		exit_ctl(data_t *pathdata, pipecon_t *pipes, const char *msg);
int		err_relay(const char *msg);

#endif
