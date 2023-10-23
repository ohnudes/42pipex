/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaturan <nmaturan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 22:16:27 by nmaturan          #+#    #+#             */
/*   Updated: 2023/10/23 21:40:12 by nmaturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"


char	*get_path(const char **env)
{
	while (ft_strncmp("PATH", *env, 4) && *env)
		env++;
	return ((char *)*(env + 5));
}

/*
char	*get_path(const char *cmd, t_errctl *errctl)
{
	int		pipe_fd[2];
	pid_t	pid;
	char	*path;
	char	buffer[MAX_PATH_LENGHT];

	if (pipe(pipe_fd) == -1)
		err_handle(errctl, &errctl->pipe, "get_path/pipe error");
	pid = fork();
	if (pid == -1)
		err_handle(errctl, &errctl->fork, "get_path/fork error");
	if (pid == 0) 	
	{
		close(pipe_fd[READ_END]);
		dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
		close(pipe_fd[WRITE_END]);
	}
}
*/

int	main(int argc, char **argv, const char *env[])
{
	t_bodyctl	pipex;

	pipex = (t_bodyctl){};
	if (argc != 5) // ./pipex cmd | 
		err_handle(&pipex.errctl, &pipex.errctl.argc, "main/argc error");
	pipex.rawpath = get_path(env);
	pipex.paths = ft_split(pipex.rawpath, ':');
}
