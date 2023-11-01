/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaturan <nmaturan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 22:16:27 by nmaturan          #+#    #+#             */
/*   Updated: 2023/11/01 18:33:32 by nmaturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>

static char	*get_path(char **env)
{
	while (ft_strncmp("PATH", *env, 4) && *env)
		env++;
	return (*env + 5);
}

static char	**finish_paths(char **vector)
{
	char	*swp;
	size_t	i;
	
	if (!vector || !*vector)
	{
		perror("init_paths/finish_paths/no_str_found");
		return (NULL);
	}
	i = 0;
	while (vector[i])
	{
		swp = vector[i];
		vector[i] = ft_strjoin(vector[i], "/");
		free(swp);
		i++;
	}
	return (vector);
}

int	init_path(t_pathdata *pathdata, char **av, char **env)
{
	char	*tmp;

	tmp = get_path(env);
	pathdata->paths = ft_split(tmp, ':');
	pathdata->paths = finish_paths(pathdata->paths);
	if (pathdata->paths == NULL) //add '/' at the end
		err_msg("init_paths/pathdata->paths_error: ");
	pathdata->rawcmd1 = ft_split(av[2], ' ');
	if (pathdata->rawcmd1 == NULL)
	{
		pathdata->paths = free_dchar(pathdata->paths);
		err_msg("init_paths/pathdata->cmd1_error: ");
	}
	pathdata->rawcmd2 = ft_split(av[3], ' ');
	if (pathdata->rawcmd2 == NULL)
	{
		pathdata->paths = free_dchar(pathdata->paths);
		pathdata->rawcmd1 = free_dchar(pathdata->rawcmd1);
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

void	cmd_check(t_pathdata *pathdata, char ***rawcmd, char *av[])
{
	size_t	i;
	char	*tmp;
	char	*testcmd;

	i = -1;
	while (pathdata->paths[++i])//check if protected!
	{
		tmp = ft_strjoin(pathdata->paths[i], "/");
		if (!tmp)
			perror("cmd_check/strjoin_failed: tmp ");
		testcmd = ft_strjoin(tmp, **rawcmd);
		if (!testcmd)
			perror("cmd_check/strjoin_failed: testcmd ");
		free(tmp);
		if (access(testcmd, 0) == 0)
		{
			*rawcmd = &testcmd;
			return ;
		}
		free(testcmd);
	}
	*rawcmd = NULL;
}
