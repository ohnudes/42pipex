/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaturan <nmaturan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:00:43 by nmaturan          #+#    #+#             */
/*   Updated: 2023/11/06 13:14:35 by nmaturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static char	*get_path(char **env)
{
	while (ft_strncmp("PATH", *env, 4) && *env)
		env++;
	errno = 0;
	return (*env + 5);
}

static char	**fill_paths(char *raw, char **vector, size_t *path_len)
{
	char	*swp;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	vector = ft_split(raw, ':');
	if (!vector)
		return (NULL);
	while (vector[i])
	{
		swp = vector[i];
		j = ft_strlen(swp);
		if (swp[j - 1] != '/')
		{
			vector[i] = ft_strjoin(vector[i], "/");
			free(swp);
		}
		i++;
	}
	*path_len = i;
	errno = 0;
	return (vector);
}

int	init_path(data_t *pdata, char **av, char **env)
{
	char	*tmp;

	tmp = get_path(env);
	if (tmp)
	{
		pdata->paths = fill_paths(tmp, pdata->paths, &pdata->path_len);
		if (pdata->paths)
		{
			pdata->rawcmd[0] = ft_split(av[2], ' ');
			if (pdata->rawcmd[0])
				pdata->rawcmd[1] = ft_split(av[3], ' ');
			if (pdata->rawcmd[0] && pdata->rawcmd[1])
			{
				errno = 0;
				return (0);
			}
		}
	}
	exit_mem(pdata);
	return (-1);
}

int	cmd_check(data_t *pathdata, char **rawcmd[2])
{
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	while (++i < pathdata->path_len)
	{
		pathdata->cmd_path[j] = ft_strjoin(pathdata->paths[i], *rawcmd[j]);
		if (access(pathdata->cmd_path[j], 0) == 0)
		{
			if (j + 1 == 2)
				break ;
			j++;
			i = 0;
		}
		else
			free(pathdata->cmd_path[j]);
	}
	if (pathdata->cmd_path[j] == NULL)
	{
		perror("cmd_check check");
		return (-1);
	}
	errno = 0;
	return (0);
}

int	init_pipe_values(pipecon_t *pipe, char **argv)
{
	pipe->ft[0] = open(argv[1], O_RDONLY);
	if (pipe->ft[0] == -1)
	{
		perror("init_pipe_values/inline: not valid");
		return (-1);
	}
	pipe->ft[1] = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (pipe->ft[1] == -1)
	{
		close(pipe->ft[0]);
		perror("init_pipe_values/outline: error");
		return (-1);
	}
	errno = 0;
	return (0);
}
