/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 23:46:31 by tmatis            #+#    #+#             */
/*   Updated: 2021/02/03 22:06:16 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	t_bool	ft_issign(char c)
{
	return (c == '+' || c == ' ' || c == '-');
}

static	int		ft_isbegin(char *s)
{
	if (ft_memcmp(s, "0x", 2) == 0 || ft_memcmp(s, "0X", 2) == 0)
		return (2);
	return (0);
}

int				ft_int_conv(t_syntax syntax, t_buffer *buffer, long long i)
{
	char			buff[BUFFER_SIZE];
	int				numlen;
	char			*pretends;
	int				index;

	pretends = " 0";
	index = 0;
	numlen = ft_buffnbr_signed(i, "0123456789", syntax, buff);
	if (!syntax.align_left && syntax.zero && syntax.precision == -1
		&& ft_issign(buff[0]))
	{
		ft_buff_fill(buffer, buff[0], 1);
		index = 1;
	}
	if (!syntax.align_left && syntax.width)
		ft_buff_fill(buffer, pretends[syntax.zero && syntax.precision == -1],
				syntax.width - numlen);
	ft_buffcat(buffer, &buff[index], numlen - index);
	if (syntax.align_left && syntax.width)
		ft_buff_fill(buffer, ' ', syntax.width - numlen);
	if (syntax.width > numlen)
		return (syntax.width);
	else
		return (numlen);
}

int				ft_uint_conv(t_syntax syntax, t_buffer *buffer,
		unsigned long long i)
{
	char			buff[BUFFER_SIZE];
	int				numlen;
	char			*pretends;
	int				index;

	pretends = " 0";
	index = 0;
	numlen = ft_buffnbr_unsigned(i, "0123456789", syntax, buff);
	if (!syntax.align_left && syntax.zero && syntax.precision == -1
		&& ft_issign(buff[0]))
	{
		ft_buff_fill(buffer, buff[0], 1);
		index = 1;
	}
	if (!syntax.align_left && syntax.width)
		ft_buff_fill(buffer, pretends[syntax.zero && syntax.precision == -1],
				syntax.width - numlen);
	ft_buffcat(buffer, &buff[index], numlen - index);
	if (syntax.align_left && syntax.width)
		ft_buff_fill(buffer, ' ', syntax.width - numlen);
	if (syntax.width > numlen)
		return (syntax.width);
	else
		return (numlen);
}

int				ft_uhex_conv(t_syntax s, t_buffer *buffer,
		unsigned long long i, t_bool upp)
{
	char			buff[BUFFER_SIZE];
	int				nl;
	char			*prt;
	int				index;

	prt = " 0";
	index = 0;
	if (upp)
		nl = ft_buffnbr_unsigned(i, "0123456789ABCDEF", s, buff);
	else
		nl = ft_buffnbr_unsigned(i, "0123456789abcdef", s, buff);
	if (!s.align_left && s.zero && s.precision == -1)
	{
		index = ft_isbegin(buff);
		ft_buffcat(buffer, buff, index);
	}
	if (!s.align_left && s.width)
		ft_buff_fill(buffer, prt[s.zero && s.precision == -1], s.width - nl);
	ft_buffcat(buffer, &buff[index], nl - index);
	if (s.align_left && s.width)
		ft_buff_fill(buffer, ' ', s.width - nl);
	if (s.width > nl)
		return (s.width);
	else
		return (nl);
}
