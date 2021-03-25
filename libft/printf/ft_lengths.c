/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lengths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 15:52:43 by tmatis            #+#    #+#             */
/*   Updated: 2021/01/02 17:19:35 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_def_conversion(t_syntax syntax, t_buffer *buffer, va_list va)
{
	int	((*conv[13])(t_syntax syntax, t_buffer *buffer, va_list va));

	conv[0] = &ft_char_def;
	conv[1] = &ft_str_def;
	conv[2] = &ft_ptr_def;
	conv[3] = &ft_int_def;
	conv[4] = &ft_int_def;
	conv[5] = &ft_uint_def;
	conv[6] = &ft_uhex_def;
	conv[7] = &ft_uhex_def;
	conv[8] = &ft_prc_def;
	conv[9] = &ft_n_def;
	return (conv[syntax.type](syntax, buffer, va));
}

int	ft_l_conversion(t_syntax syntax, t_buffer *buffer, va_list va)
{
	int	((*conv[13])(t_syntax syntax, t_buffer *buffer, va_list va));

	conv[0] = &ft_char_l;
	conv[1] = &ft_str_l;
	conv[2] = &ft_ptr_def;
	conv[3] = &ft_int_l;
	conv[4] = &ft_int_l;
	conv[5] = &ft_uint_l;
	conv[6] = &ft_uhex_l;
	conv[7] = &ft_uhex_l;
	conv[8] = &ft_prc_def;
	conv[9] = &ft_n_l;
	return (conv[syntax.type](syntax, buffer, va));
}

int	ft_ll_conversion(t_syntax syntax, t_buffer *buffer, va_list va)
{
	int	((*conv[13])(t_syntax syntax, t_buffer *buffer, va_list va));

	conv[0] = &ft_char_def;
	conv[1] = &ft_str_def;
	conv[2] = &ft_ptr_def;
	conv[3] = &ft_int_ll;
	conv[4] = &ft_int_ll;
	conv[5] = &ft_uint_ll;
	conv[6] = &ft_uhex_ll;
	conv[7] = &ft_uhex_ll;
	conv[8] = &ft_prc_def;
	conv[9] = &ft_n_ll;
	return (conv[syntax.type](syntax, buffer, va));
}

int	ft_h_conversion(t_syntax syntax, t_buffer *buffer, va_list va)
{
	int	((*conv[13])(t_syntax syntax, t_buffer *buffer, va_list va));

	conv[0] = &ft_char_def;
	conv[1] = &ft_str_def;
	conv[2] = &ft_ptr_def;
	conv[3] = &ft_int_h;
	conv[4] = &ft_int_h;
	conv[5] = &ft_uint_h;
	conv[6] = &ft_uhex_h;
	conv[7] = &ft_uhex_h;
	conv[8] = &ft_prc_def;
	conv[9] = &ft_n_h;
	return (conv[syntax.type](syntax, buffer, va));
}

int	ft_hh_conversion(t_syntax syntax, t_buffer *buffer, va_list va)
{
	int	((*conv[13])(t_syntax syntax, t_buffer *buffer, va_list va));

	conv[0] = &ft_char_def;
	conv[1] = &ft_str_def;
	conv[2] = &ft_ptr_def;
	conv[3] = &ft_int_hh;
	conv[4] = &ft_int_hh;
	conv[5] = &ft_uint_hh;
	conv[6] = &ft_uhex_hh;
	conv[7] = &ft_uhex_hh;
	conv[8] = &ft_prc_def;
	conv[9] = &ft_n_hh;
	return (conv[syntax.type](syntax, buffer, va));
}
