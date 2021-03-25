/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parseutils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:19:36 by tmatis            #+#    #+#             */
/*   Updated: 2021/01/02 17:11:59 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_syntax	ft_parseflags(const char **format, t_syntax syntax)
{
	char	*charset;

	charset = "-+ 0#";
	while (ft_christr(charset, **format) != -1)
	{
		if (**format == '-')
			syntax.align_left = true;
		else if (**format == '+')
			syntax.plus = true;
		else if (**format == ' ')
			syntax.space = true;
		else if (**format == '0')
			syntax.zero = true;
		else if (**format == '#')
			syntax.hash = true;
		(*format)++;
	}
	return (syntax);
}

t_syntax	ft_parsewidth(const char **format, t_syntax syntax, va_list va)
{
	int		width;

	if (**format == '*')
	{
		width = va_arg(va, int);
		if (width < 0)
		{
			syntax.width = -width;
			syntax.align_left = true;
		}
		else
			syntax.width = width;
		(*format)++;
	}
	else
	{
		syntax.width = ft_atoi(*format);
		while (ft_isdigit(**format))
			(*format)++;
	}
	return (syntax);
}

t_syntax	ft_parseprecision(const char **format, t_syntax syntax, va_list va)
{
	int	precision;

	precision = 0;
	if (**format == '.')
	{
		(*format)++;
		if (**format == '*')
		{
			(*format)++;
			precision = va_arg(va, int);
			if (precision >= 0)
				syntax.precision = precision;
		}
		else
		{
			while (**format && ft_isdigit(**format))
				precision = precision * 10 + (*(*format)++ - 48);
			syntax.precision = precision;
		}
	}
	return (syntax);
}

t_syntax	ft_parselength(const char **format, t_syntax syntax)
{
	if (ft_strncmp(*format, "ll", 2) == 0)
	{
		syntax.length = ll;
		(*format) += 2;
	}
	else if (ft_strncmp(*format, "hh", 2) == 0)
	{
		syntax.length = hh;
		(*format) += 2;
	}
	else if (ft_strncmp(*format, "h", 1) == 0)
	{
		syntax.length = h;
		(*format)++;
	}
	else if (ft_strncmp(*format, "l", 1) == 0)
	{
		syntax.length = l;
		(*format)++;
	}
	return (syntax);
}

t_syntax	ft_parsetype(const char **format, t_syntax syntax)
{
	char	*charset;

	charset = "cspdiuxX%n";
	syntax.type = ft_christr(charset, **format);
	if (**format && syntax.type != -1)
		(*format)++;
	return (syntax);
}
