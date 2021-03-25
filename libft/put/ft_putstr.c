/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 14:53:42 by tmatis            #+#    #+#             */
/*   Updated: 2021/03/20 16:52:25 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"
#include <unistd.h>

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

void	ft_putnl(char *str)
{
	ft_putstr(str);
	ft_putstr("\n");
}
