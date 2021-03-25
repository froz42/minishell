/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 14:36:22 by tmatis            #+#    #+#             */
/*   Updated: 2021/02/03 22:12:05 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int	ft_printfutils(const char *format, va_list va, t_buffer *buffer)
{
	t_syntax	syntax;
	int			count;

	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			syntax = ft_parsesyntax(&format, va);
			syntax.count = count;
			count += ft_doconversion(syntax, buffer, va);
		}
		else
		{
			ft_buffcat(buffer, format++, 1);
			count++;
		}
	}
	return (count);
}

int			ft_printf(const char *format, ...)
{
	t_buffer	buffer;
	va_list		va;
	int			count;

	buffer = ft_buffinit(1);
	va_start(va, format);
	count = ft_printfutils(format, va, &buffer);
	va_end(va);
	ft_buffflush(&buffer);
	return (count);
}

int			ft_dprintf(int fd, const char *format, ...)
{
	t_buffer	buffer;
	va_list		va;
	int			count;

	buffer = ft_buffinit(fd);
	va_start(va, format);
	count = ft_printfutils(format, va, &buffer);
	va_end(va);
	ft_buffflush(&buffer);
	return (count);
}

int			ft_sprintf(char *str, const char *format, ...)
{
	t_buffer	buffer;
	va_list		va;
	int			count;

	buffer = ft_buffinit(-1);
	va_start(va, format);
	count = ft_printfutils(format, va, &buffer);
	va_end(va);
	ft_memcpy(str, buffer.content, buffer.size);
	return (count);
}
