/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaturan <nmaturan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:59:50 by nmaturan          #+#    #+#             */
/*   Updated: 2023/11/01 16:20:34 by nmaturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_all(char **vector, size_t count)
{
	while (count)
	{
		count--;
		free(vector[count]);
	}
	free(vector);
	return (NULL);
}

static size_t	str_count(const char *str, const char c)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
			count++;
		while (str[i] && str[i] != c)
			i++;
		while (str[i] && str[i] == c)
			i++;
	}
	return (count);
}

static size_t	str_len(const char *str, const char c)
{
	size_t	len;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	return (len);
}

char	**ft_split(const char *str, const char c)
{
	char	**vector;
	size_t	word_count;
	size_t	count;
	size_t	i;

	word_count = str_count(str, c);
	vector = malloc(sizeof(char **) * (word_count + 1));
	vector[word_count] = NULL;
	if (!vector)
		return (NULL);
	count = 0;
	i = 0;
	while (count < word_count)
	{
		if (str[i] && str[i] != c)
		{
			vector[count] = ft_substr(str, i, str_len((str + i), c));
			if (!vector[count])
				return (free_all(vector, count));
			count++;
		}
		while (str[i] && str[i] != c)
			i++;
		while (str[i] && str[i] == c)
			i++;
	}
	vector[count] = NULL;
	return (vector);
}
