/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 17:11:17 by sabrugie          #+#    #+#             */
/*   Updated: 2021/05/29 17:25:07 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_putdstr(int fd, char *str, uint8_t newline)
{
	if (!str)
		return ;
	write(fd, str, ft_strlen(str));
	if (newline)
		write(fd, "\n", 1);
}
