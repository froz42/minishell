/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_alpha.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 11:59:22 by tmatis            #+#    #+#             */
/*   Updated: 2021/01/04 16:35:03 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include "../char/char.h"

int	ft_str_is_alpha(char *str)
{
	while (*str && ft_isalpha(*str))
		str++;
	return (!*str || ft_isalpha(*str));
}
