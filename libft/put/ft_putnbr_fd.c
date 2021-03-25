/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 12:05:34 by tmatis            #+#    #+#             */
/*   Updated: 2021/01/04 16:01:24 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	un;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		un = -n;
	}
	else
		un = n;
	if (un > 9)
	{
		ft_putnbr_fd(un / 10, fd);
		ft_putchar_fd((un % 10) + 48, fd);
	}
	else
		ft_putchar_fd(un + 48, fd);
}
