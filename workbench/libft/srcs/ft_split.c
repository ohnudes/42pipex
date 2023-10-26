/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaturan <nmaturan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:59:50 by nmaturan          #+#    #+#             */
/*   Updated: 2023/10/26 17:53:27 by nmaturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_all(char **big, size_t little)
{
	while (little)
	{
		little--;
		free(big[little]);
	}
	free(big);
	return (NULL);
}

static char	**str_count_and_size(const char *str, const char set)
{
	char	**mem_alloc;
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != set)
			count++;
		while (str[i] && str[i] != set)
			i++;
		while (str[i] && str[i] == set)
			i++;
	}
	mem_alloc = NULL;
	mem_alloc = malloc(sizeof(char **) * (count + 1));
	return (mem_alloc);
}

static size_t	str_len(const char *str, const char set)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != set)
		i++;
	return (i);
}

char	**ft_split(const char *str, const char set)
{
	char	**big;
	size_t	little;
	size_t	i;

	big = str_count_and_size(str, set);	
	if (!big)
		return (NULL);
	little = 0;
	i = 0;
	while (little < str_count(str, set))
	{
		if (str[i] && str[i] != set)
		{
			big[little] = ft_substr(str, i, str_len((str + i), set));
			if (!big[little])
				return (free_all(big, little));
			little++;
		}
		while (str[i] && str[i] != set)
			i++;
		while (str[i] && str[i] == set)
			i++;
	}
	big[little] = NULL;
	return (big);
}
