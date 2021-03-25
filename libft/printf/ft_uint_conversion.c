/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uint_conversion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 16:24:22 by tmatis            #+#    #+#             */
/*   Updated: 2021/01/02 18:12:37 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_uint_def(t_syntax syntax, t_buffer *buffer, va_list va)
{
	return (ft_uint_conv(syntax, buffer, va_arg(va, unsigned int)));
}

int	ft_uint_hh(t_syntax syntax, t_buffer *buffer, va_list va)
{
	return (ft_uint_conv(syntax, buffer,
			(unsigned char)va_arg(va, unsigned int)));
}

int	ft_uint_h(t_syntax syntax, t_buffer *buffer, va_list va)
{
	return (ft_uint_conv(syntax, buffer,
			(unsigned short)va_arg(va, unsigned int)));
}

int	ft_uint_l(t_syntax syntax, t_buffer *buffer, va_list va)
{
	return (ft_uint_conv(syntax, buffer, va_arg(va, unsigned long)));
}

int	ft_uint_ll(t_syntax syntax, t_buffer *buffer, va_list va)
{
	return (ft_uint_conv(syntax, buffer, va_arg(va, unsigned long long)));
}
