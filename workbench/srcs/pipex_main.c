/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaturan <nmaturan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:20:19 by nmaturan          #+#    #+#             */
/*   Updated: 2023/10/26 17:25:47 by nmaturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <sys/wait.h>

void	end_pipex(t_pipex *pipex)
{
	pipex->pathdata.paths = free_dchar(pipex->pathdata.paths);
	pipex->pathdata.cmd1 = free_dchar(pipex->pathdata.cmd1);
	pipex->pathdata.cmd2 = free_dchar(pipex->pathdata.cmd2);
	close(pipex->connection.ft1);
	close(pipex->connection.ft2);
}

void	body(t_pipex *pipex)
{
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
	waitpid(child1, int *stat_loc, int options)
	waitpid(child2, int *stat_loc, int options)
}

int	main(int ac, char **av, char *env[])
{
	t_pipex	pipex;

	if (ac != 5)
		err_msg("argcount error: ");
	pipex = (t_pipex){};
	init_fd(&pipex.connection, av);
	init_path(&pipex.pathdata, av, env);
	body(&pipex);
	end_pipex(&pipex);
	return (0);
}
