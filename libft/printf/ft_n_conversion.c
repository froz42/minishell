/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_n_conversion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:37:39 by tmatis            #+#    #+#             */
/*   Updated: 2021/01/02 18:08:48 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_n_def(t_syntax syntax, t_buffer *buffer, va_list va)
{
	int	*p;

	(void)buffer;
	p = va_arg(va, int *);
	*p = syntax.count;
	return (0);
}

int	ft_n_hh(t_syntax syntax, t_buffer *buffer, va_list va)
{
	char	*p;

	(void)buffer;
	p = va_arg(va, char *);
	*p = syntax.count;
	return (0);
}

int	ft_n_h(t_syntax syntax, t_buffer *buffer, va_list va)
{
	short	*p;

	(void)buffer;
	p = va_arg(va, short *);
	*p = syntax.count;
	return (0);
}

int	ft_n_l(t_syntax syntax, t_buffer *buffer, va_list va)
{
	long	*p;

	(void)buffer;
	p = va_arg(va, long *);
	*p = syntax.count;
	return (0);
}

int	ft_n_ll(t_syntax syntax, t_buffer *buffer, va_list va)
{
	long long	*p;

	(void)buffer;
	p = va_arg(va, long long *);
	*p = syntax.count;
	return (0);
}
