/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uhex_conversion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 16:23:32 by tmatis            #+#    #+#             */
/*   Updated: 2021/01/02 18:12:02 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_uhex_def(t_syntax syntax, t_buffer *buffer, va_list va)
{
	return (ft_uhex_conv(syntax, buffer, va_arg(va,
				unsigned int), syntax.type == 7));
}

int	ft_uhex_ll(t_syntax syntax, t_buffer *buffer, va_list va)
{
	return (ft_uhex_conv(syntax, buffer,
			va_arg(va, unsigned long long), syntax.type == 7));
}

int	ft_uhex_l(t_syntax syntax, t_buffer *buffer, va_list va)
{
	return (ft_uhex_conv(syntax, buffer,
			va_arg(va, unsigned long), syntax.type == 7));
}

int	ft_uhex_hh(t_syntax syntax, t_buffer *buffer, va_list va)
{
	return (ft_uhex_conv(syntax, buffer,
			(unsigned char)va_arg(va, int), syntax.type == 7));
}

int	ft_uhex_h(t_syntax syntax, t_buffer *buffer, va_list va)
{
	return (ft_uhex_conv(syntax, buffer,
			(unsigned short)va_arg(va, int), syntax.type == 7));
}
