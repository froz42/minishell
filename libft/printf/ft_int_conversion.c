/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_conversion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 16:42:08 by tmatis            #+#    #+#             */
/*   Updated: 2021/01/02 20:18:46 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_int_def(t_syntax syntax, t_buffer *buffer, va_list va)
{
	return (ft_int_conv(syntax, buffer, va_arg(va, int)));
}

int	ft_int_hh(t_syntax syntax, t_buffer *buffer, va_list va)
{
	return (ft_int_conv(syntax, buffer, (char)va_arg(va, int)));
}

int	ft_int_h(t_syntax syntax, t_buffer *buffer, va_list va)
{
	return (ft_int_conv(syntax, buffer, (short)va_arg(va, int)));
}

int	ft_int_l(t_syntax syntax, t_buffer *buffer, va_list va)
{
	return (ft_int_conv(syntax, buffer, va_arg(va, long)));
}

int	ft_int_ll(t_syntax syntax, t_buffer *buffer, va_list va)
{
	return (ft_int_conv(syntax, buffer, va_arg(va, long long)));
}
