/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaturan <nmaturan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:43:51 by nmaturan          #+#    #+#             */
/*   Updated: 2023/11/06 13:14:43 by nmaturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static int	child_two(data_t *pdata, pipecon_t *pipes, char **envp)
{
	dup2(pipes->fd[0], STDIN_FILENO);
	dup2(pipes->ft[1], STDOUT_FILENO);
	close(pipes->fd[1]);
	close(pipes->fd[0]);
	if (execve(pdata->cmd_path[1], pdata->rawcmd[1], envp) == -1)
		return (err_relay("child_one/execve == -1"));
	errno = 0;
	exit(EXIT_SUCCESS);
}

static int	child_one(data_t *pdata, pipecon_t *pipes, char **envp)
{
	dup2(pipes->ft[0], STDIN_FILENO);
	dup2(pipes->fd[1], STDOUT_FILENO);
	close(pipes->fd[0]);
	close(pipes->fd[1]);
	if (execve(pdata->cmd_path[0], pdata->rawcmd[0], envp) == -1)
		return (err_relay("child_one/execve == -1"));
	errno = 0;
	exit(EXIT_SUCCESS);
}

int	body(data_t *pdata, pipecon_t *pipes, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pipes->fd) == -1)
		return (err_relay("body/pipe(fd): pipe == -1"));
	pid1 = fork();
	if (pid1 == -1)
		return (err_relay("body/fork/pid1: pid1 == -1"));
	if (pid1 == 0)
		child_one(pdata, pipes, envp);
	pid2 = fork();
	if (pid2 == -1)
		return (err_relay("body/fork/pid2: pid2 == -1"));
	if (pid2 == 0)
		child_two(pdata, pipes, envp);
	close(pipes->fd[0]);
	close(pipes->fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	exit_mem(pdata);
	exit_pipes(pipes);
	errno = 0;
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	data_t		pathdata;
	pipecon_t	pipes;

	if (argc != 5)
	{
		perror("argc count error");
		return (0);
	}
	pathdata = (data_t){};
	pipes = (pipecon_t){};
	if (init_path(&pathdata, argv, envp) == -1)
		return (exit_ctl(&pathdata, &pipes, "init_path/returns -1"));
	if (cmd_check(&pathdata, pathdata.rawcmd) == -1)
		return (exit_ctl(&pathdata, &pipes, "cmd_check/returns -1"));
	if (init_pipe_values(&pipes, argv) == -1)
		return (exit_ctl(&pathdata, &pipes, "init_pipe_values/returns -1"));
	if (body(&pathdata, &pipes, envp) == -1)
		return (exit_ctl(&pathdata, &pipes, "main/body/returns -1"));
	errno = 0;
	return (0);
}
