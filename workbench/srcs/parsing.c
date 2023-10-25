/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaturan <nmaturan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 22:16:27 by nmaturan          #+#    #+#             */
/*   Updated: 2023/10/25 16:20:16 by nmaturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*get_path(const char **env)
{
	while (ft_strncmp("PATH", *env, 4) && *env)
		env++;
	return ((char *)*(env + 5));
}
