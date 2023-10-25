/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaturan <nmaturan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:20:19 by nmaturan          #+#    #+#             */
/*   Updated: 2023/10/25 16:21:18 by nmaturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, const char *env[])
{
	t_bodyctl	pipex;

	pipex = (t_bodyctl){};
	if (argc != 5) // ./pipex cmd | 
		err_handle(&pipex.errctl, &pipex.errctl.argc, "main/argc error");
	pipex.rawpath = get_path(env);
	pipex.paths = ft_split(pipex.rawpath, ':');
}

