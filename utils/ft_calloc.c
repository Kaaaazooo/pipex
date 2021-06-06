/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 11:35:26 by sabrugie          #+#    #+#             */
/*   Updated: 2021/06/06 17:32:25 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*str;
	size_t			total;
	size_t			i;

	i = 0;
	total = count * size;
	str = (unsigned char *)malloc(total);
	if (!str)
		return (0);
	while (i < total)
		str[i++] = 0;
	return ((void *)str);
}
