/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaturan <nmaturan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 22:16:27 by nmaturan          #+#    #+#             */
/*   Updated: 2023/10/26 17:19:58 by nmaturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char **env)
{
	while (ft_strncmp("PATH", *env, 4) && *env)
		env++;
	return (*env + 5);
}

void	init_path(t_pathdata *pathdata, char **av, char **env)
{
	char	*tmp;

	tmp = get_path(env);
	pathdata->paths = ft_split(tmp, ':');
	if (pathdata->paths == NULL) //add '/' at the end
		err_msg("init_paths/pathdata->paths_error: ");
	pathdata->cmd1 = ft_split(av[2], ' ');
	if (pathdata->cmd1 == NULL)
	{
		pathdata->paths = free_dchar(pathdata->paths);
		err_msg("init_paths/pathdata->cmd1_error: ");
	}
	pathdata->cmd2 = ft_split(av[3], ' ');
	if (pathdata->cmd2 == NULL)
	{
		pathdata->paths = free_dchar(pathdata->paths);
		pathdata->cmd1 = free_dchar(pathdata->cmd1);
		err_msg("init_paths/pathdata->cmd2_error: ");
	}
}

void	init_fd(t_fdbridge *connection, char **av)
{
	connection->ft1 = open(av[1], O_RDONLY);
	if (connection->ft1 == -1)
	{
		perror("init_fd/open_error: ");
		exit(EXIT_FAILURE);
	}
	connection->ft2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (connection->ft2 == -1)
	{
		close(connection->ft1);
		perror("init_fd/open_error: ");
		exit(EXIT_FAILURE);
	}
}

