/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaturan <nmaturan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 15:52:54 by nmaturan          #+#    #+#             */
/*   Updated: 2023/10/31 21:29:51 by nmaturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static	int	isset(const char *set, char c)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(const char *str, const char *set)
{
	size_t	i;
	size_t	ri;
	char	*res;

	if (!str)
		return (ft_strdup(""));
	i = 0;
	ri = ft_strlen(str);
	while (i < ri && isset(set, str[i]))
		i++;
	while (ri > i && isset(set, str[ri - 1]))
		ri--;
	if (i == ri)
		return (ft_strdup(""));
	res = malloc(sizeof(char) * (ri - i + 1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, str + i, ri - i + 1);
	return (res);
}
