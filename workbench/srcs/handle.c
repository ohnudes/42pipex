/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaturan <nmaturan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:51:30 by nmaturan          #+#    #+#             */
/*   Updated: 2023/10/23 21:15:39 by nmaturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*err_handle(t_errctl *errctl, int *errtype, const char *msg)
{
	errctl->exit = -1;
	*errtype = -1;
	perror(msg);
	exit (1);
}
