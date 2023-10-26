/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaturan <nmaturan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:20:19 by nmaturan          #+#    #+#             */
/*   Updated: 2023/10/26 20:52:41 by nmaturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <sys/wait.h>

void	end_pipex(t_pipex *pipex)
{
	if (pipex->pathdata.paths)
		pipex->pathdata.paths = free_dchar(pipex->pathdata.paths);
	if (pipex->pathdata.rawcmd1)
		pipex->pathdata.rawcmd1 = free_dchar(pipex->pathdata.rawcmd1);
	if (pipex->pathdata.rawcmd2)
		pipex->pathdata.rawcmd2 = free_dchar(pipex->pathdata.rawcmd2);
	if (pipex->pathdata.cmd1path)
		pipex->pathdata.cmd1path = free_dchar(pipex->pathdata.cmd1path);
	if (pipex->pathdata.cmd2path)
		pipex->pathdata.cmd2path = free_dchar(pipex->pathdata.cmd2path);
	close(pipex->connection.ft1);
	close(pipex->connection.ft2);
}

void	body(t_pipex *pipex, char *env[])
{
	int		status;
	pid_t	child1;
	pid_t	child2;

	if (pipe(pipex->connection.fd) == -1)
		end_pipex(pipex);
	child1 = fork();
	if (child1 == -1)
		err_msg("main/fork error: ");
	if (child1 == 0)
		child_one(pipex->connection.ft1, );
	child2 = fork();
	if (child2 == -1)
		err_msg("main/fork error: ");
	if (child2 == 0)
		child_two(pipex->connection.ft1, );
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
}

int	main(int ac, char **av, char *env[])
{
	t_pipex	pipex;

	if (ac != 5)
		err_msg("argcount error: ");
	pipex = (t_pipex){};
	init_fd(&pipex.connection, av);
	init_path(&pipex.pathdata, av, env);
	cmd_check(&pipex.pathdata, &pipex.pathdata.rawcmd1, av);
	cmd_check(&pipex.pathdata, &pipex.pathdata.rawcmd2, av);
	if (!pipex.pathdata.rawcmd1 || !pipex.pathdata.rawcmd2)
		end_pipex(&pipex);
	body(&pipex, env);
	end_pipex(&pipex);
	return (0);
}
