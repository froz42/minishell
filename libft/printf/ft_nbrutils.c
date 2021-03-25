/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 16:22:56 by tmatis            #+#    #+#             */
/*   Updated: 2021/02/03 22:09:36 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static	int						ft_numlen_base(
		unsigned long long i, int base, int precision)
{
	int		len;

	len = 0;
	while (i)
	{
		len++;
		i /= base;
	}
	if (len == 0 && precision != 0)
		len++;
	return (len);
}

static unsigned	long	long	ft_signhandle(
		long long si, char **buff, t_syntax s)
{
	if (si < 0)
	{
		*(*buff)++ = '-';
		return (-si);
	}
	else if (s.plus)
		*(*buff)++ = '+';
	else if (s.space)
		*(*buff)++ = ' ';
	return (si);
}

static	void					ft_beginhandle(
		char **buff, t_syntax s, int bl, long long nbr)
{
	if ((s.hash && bl == 16 && nbr) || s.type == 2)
	{
		if (s.type == 7)
			ft_memcpy(*buff, "0X", 2);
		else
			ft_memcpy(*buff, "0x", 2);
		(*buff) += 2;
	}
}

int								ft_buffnbr_unsigned(
		unsigned long long i, char *base, t_syntax s, char *buff)
{
	int		base_len;
	int		num_len;
	char	*temp;

	base_len = ft_strlen(base);
	temp = buff;
	ft_beginhandle(&buff, s, base_len, i);
	num_len = ft_numlen_base(i, base_len, s.precision);
	if (num_len > s.precision)
		s.precision = num_len;
	buff[s.precision] = '\0';
	while (s.precision--)
	{
		buff[s.precision] = base[i % base_len];
		i /= base_len;
	}
	return (ft_strlen(temp));
}

int								ft_buffnbr_signed(
		long long si, char *base, t_syntax s, char *buff)
{
	int								base_len;
	int								num_len;
	char							*temp;
	unsigned	long	long		i;

	base_len = ft_strlen(base);
	temp = buff;
	i = ft_signhandle(si, &buff, s);
	num_len = ft_numlen_base(i, base_len, s.precision);
	if (num_len > s.precision)
		s.precision = num_len;
	buff[s.precision] = '\0';
	while (s.precision--)
	{
		buff[s.precision] = base[i % base_len];
		i /= base_len;
	}
	return (ft_strlen(temp));
}
