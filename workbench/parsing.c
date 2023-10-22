/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaturan <nmaturan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 22:16:27 by nmaturan          #+#    #+#             */
/*   Updated: 2023/10/22 22:42:23 by nmaturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"
#include <unistd.h>

char	*err_handle(int *errctl, int errvalue, const char *msg)
{
	*errctl = errvalue;
	perror(msg);
	return (NULL);
}

char	*get_path(const char *cmd, t_errctl *errctl)
{
	int		pipe_fd[2];
	pid_t	pid;
	char	*path;
	char	buffer[MAX_PATH_LENGHT];

	if (pipe(pipe_fd) == -1)
		return (err_handle(&errctl->pipe, -1, "get_path/pipe error"));
	pid = fork();
	if (pid == -1)
		return (err_handle(&errctl->fork, -1, "get_path/fork error"));
	if (pid == 0) /* child process */
	{
		close(pipe_fd[READ_END]);
		dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
		close(pipe_fd[WRITE_END]);

	}
}

int	main(int argc, char **argv)
{
	t_bodyctl	mainctl;

	mainctl = (t_bodyctl){};
	mainctl.pathdata = get_path("echo $PATH", &mainctl.errctl);

	
}
