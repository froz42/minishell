/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_conversion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 13:16:03 by tmatis            #+#    #+#             */
/*   Updated: 2021/02/03 22:11:10 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_str_def(t_syntax syntax, t_buffer *buffer, va_list va)
{
	char			*pretends;
	char			*nullstr;
	char			*str;
	int				strlen;

	pretends = " 0";
	nullstr = "(null)";
	str = va_arg(va, char *);
	if (!str)
		str = (char *)nullstr;
	if (syntax.precision != -1)
		strlen = ft_strnlen(str, syntax.precision);
	else
		strlen = ft_strlen(str);
	if (!syntax.align_left && syntax.width)
		ft_buff_fill(buffer, pretends[syntax.zero], syntax.width - strlen);
	ft_buffcat(buffer, str, strlen);
	if (syntax.align_left && syntax.width)
		ft_buff_fill(buffer, ' ', syntax.width - strlen);
	if (syntax.width && syntax.width > strlen)
		return (syntax.width);
	else
		return (strlen);
}

static	int		ft_wstrlenp(const int *wstr, int precision)
{
	char	buff[4];
	int		strlen;
	int		buffed;

	strlen = 0;
	while (*wstr)
	{
		buffed = ft_utf8_encode(*wstr++, buff);
		if (precision != -1 && (strlen + buffed) > precision)
			return (strlen);
		strlen += buffed;
	}
	return (strlen);
}

static	void	ft_buffwcat(t_buffer *buffer, const int *wstr, int prec)
{
	char	buff[4];
	int		buffed;
	int		strlen;

	strlen = 0;
	while (*wstr)
	{
		buffed = ft_utf8_encode(*wstr++, buff);
		if (prec != -1 && (strlen + buffed) > prec)
			return ;
		strlen += buffed;
		if (&buffer->content[buffer->size + buffed]
			>= &buffer->content[BUFFER_SIZE])
			ft_buffflush(buffer);
		ft_buffcat(buffer, buff, buffed);
	}
}

int				ft_str_l(t_syntax syntax, t_buffer *buffer, va_list va)
{
	char	*pretends;
	int		*nullstr;
	int		*wstr;
	int		strlen;

	pretends = " 0";
	nullstr = L"(null)";
	wstr = va_arg(va, int *);
	if (!wstr)
		wstr = nullstr;
	strlen = ft_wstrlenp(wstr, syntax.precision);
	if (!syntax.align_left && syntax.width)
		ft_buff_fill(buffer, pretends[syntax.zero], syntax.width - strlen);
	ft_buffwcat(buffer, wstr, syntax.precision);
	if (syntax.align_left && syntax.width)
		ft_buff_fill(buffer, ' ', syntax.width - strlen);
	if (syntax.width && syntax.width > strlen)
		return (syntax.width);
	else
		return (strlen);
}
