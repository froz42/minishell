/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsesyntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 12:35:29 by tmatis            #+#    #+#             */
/*   Updated: 2021/02/03 22:11:40 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_syntax	ft_syntaxinit(void)
{
	t_syntax	s;

	s.align_left = false;
	s.plus = false;
	s.space = false;
	s.zero = false;
	s.hash = false;
	s.width = 0;
	s.precision = -1;
	s.length = def;
	s.type = -1;
	s.count = 0;
	return (s);
}

t_syntax	ft_parsesyntax(const char **format, va_list va)
{
	t_syntax		syntax;

	syntax = ft_syntaxinit();
	(*format)++;
	syntax = ft_parseflags(format, syntax);
	syntax = ft_parsewidth(format, syntax, va);
	syntax = ft_parseprecision(format, syntax, va);
	syntax = ft_parselength(format, syntax);
	syntax = ft_parsetype(format, syntax);
	return (syntax);
}

int			ft_doconversion(t_syntax syntax, t_buffer *buffer, va_list va)
{
	int		result;

	result = 0;
	if (syntax.type == -1)
		return (-1);
	if (syntax.length == def)
		result = ft_def_conversion(syntax, buffer, va);
	else if (syntax.length == l)
		result = ft_l_conversion(syntax, buffer, va);
	else if (syntax.length == ll)
		result = ft_ll_conversion(syntax, buffer, va);
	else if (syntax.length == h)
		result = ft_h_conversion(syntax, buffer, va);
	else if (syntax.length == hh)
		result = ft_hh_conversion(syntax, buffer, va);
	return (result);
}
