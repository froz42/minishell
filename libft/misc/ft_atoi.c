/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 18:13:16 by tmatis            #+#    #+#             */
/*   Updated: 2021/01/04 16:36:20 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "misc.h"
#include "../char/char.h"

int	ft_atoi(const char *str)
{
	int				sign;
	int unsigned	n;

	sign = 1;
	n = 0;
	while (*str && ((*str >= 9 && *str <= 13) || *str == 32))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && ft_isdigit(*str))
		n = n * 10 + ((*str++) - 48);
	return (n * sign);
}
