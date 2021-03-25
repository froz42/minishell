/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_conversion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 15:06:57 by tmatis            #+#    #+#             */
/*   Updated: 2021/01/02 19:54:07 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_char_def(t_syntax syntax, t_buffer *buffer, va_list va)
{
	char	*pretends;

	pretends = " 0";
	if (!syntax.align_left && syntax.width)
		ft_buff_fill(buffer, pretends[syntax.zero], syntax.width - 1);
	ft_buff_fill(buffer, (unsigned char)va_arg(va, int), 1);
	if (syntax.align_left && syntax.width)
		ft_buff_fill(buffer, ' ', syntax.width - 1);
	if (syntax.width)
		return (syntax.width);
	else
		return (1);
}

int	ft_char_l(t_syntax syntax, t_buffer *buffer, va_list va)
{
	char	*pretends;
	int		len;
	char	buffer_utf8[4];

	pretends = " 0";
	len = ft_utf8_encode(va_arg(va, int), buffer_utf8);
	if (!syntax.align_left && syntax.width)
		ft_buff_fill(buffer, pretends[syntax.zero], syntax.width - len);
	ft_buffcat(buffer, buffer_utf8, len);
	if (syntax.align_left && syntax.width)
		ft_buff_fill(buffer, ' ', syntax.width - len);
	if (syntax.width)
		return (syntax.width);
	else
		return (1);
}

int	ft_prc_def(t_syntax syntax, t_buffer *buffer, va_list va)
{
	char	*pretends;

	pretends = " 0";
	(void)va;
	if (!syntax.align_left && syntax.width)
		ft_buff_fill(buffer, pretends[syntax.zero], syntax.width - 1);
	ft_buff_fill(buffer, '%', 1);
	if (syntax.align_left && syntax.width)
		ft_buff_fill(buffer, ' ', syntax.width - 1);
	if (syntax.width)
		return (syntax.width);
	else
		return (1);
}
