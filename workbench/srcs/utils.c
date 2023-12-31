/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaturan <nmaturan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:39:56 by nmaturan          #+#    #+#             */
/*   Updated: 2023/11/06 13:14:48 by nmaturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	err_relay(const char *msg)
{
	perror(msg);
	return (-1);
}

int	exit_ctl(data_t *pathdata, pipecon_t *pipes, const char *msg)
{
	exit_mem(pathdata);
	exit_pipes(pipes);
	perror(msg);
	exit(0);
}

void	exit_pipes(pipecon_t *pipes)
{
	size_t	i;

	i = 0;
	while (i < 2)
	{
		close(pipes->ft[i]);
		close(pipes->fd[i]);
		i++;
	}
	return ;
}

static void	free_vec(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	while (i)
	{
		i--;
		free(str[i]);
	}
	free(str);
}

void	exit_mem(data_t *pdata)
{
	size_t	i;

	i = 0;
	if (pdata->paths)
	{
		free_vec(pdata->paths);
		pdata->paths = NULL;
	}
	while (i < 2)
	{
		if (pdata->rawcmd[i])
		{
			free_vec(pdata->rawcmd[i]);
			pdata->rawcmd[i] = NULL;
		}
		if (pdata->cmd_path[i])
		{
			free(pdata->cmd_path[i]);
			pdata->cmd_path[i] = NULL;
		}
		i++;
	}
}
