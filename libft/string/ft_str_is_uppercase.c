/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_uppercase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 12:31:51 by tmatis            #+#    #+#             */
/*   Updated: 2021/01/04 16:34:19 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include "../char/char.h"

int	ft_str_is_uppercase(char *str)
{
	while (*str && ft_isupper(*str))
		str++;
	return (!*str || ft_isupper(*str));
}
