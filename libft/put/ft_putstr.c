/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 14:53:42 by tmatis            #+#    #+#             */
/*   Updated: 2021/04/22 12:57:33 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"
#include <unistd.h>

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

void	ft_putprintable(char *str)
{
	while (*str)
	{
		if (*str >= 32 && *str <= 126)
			write(1, str, 1);
		else
			write(1, ".", 1);
		str++;
	}
}

void	ft_putnl(char *str)
{
	ft_putstr(str);
	ft_putstr("\n");
}
