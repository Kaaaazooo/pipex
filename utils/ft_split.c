/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:52:38 by sabrugie          #+#    #+#             */
/*   Updated: 2021/05/29 14:40:14 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static size_t	count(char const *s, char c)
{
	size_t		i;
	size_t		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static char	**free_strs(char **strs, int j)
{
	while (j >= 0)
		free(strs[j--]);
	free(strs);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char		**res;
	size_t		i;
	size_t		j;

	if (s)
		res = (char **)ft_calloc(sizeof(char *), (count(s, c) + 1));
	if (!s || !res)
		return (NULL);
	j = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		i = 0;
		if (*s)
		{
			while (s[i] && s[i] != c)
				i++;
			res[j] = ft_strndup(s, i);
			if (!res[j++])
				return (free_strs(res, (int)(j - 1)));
			s += i;
		}
	}
	return (res);
}
