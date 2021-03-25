/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 19:16:04 by tmatis            #+#    #+#             */
/*   Updated: 2021/02/03 22:11:22 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include "../libft.h"
# include <stdarg.h>
# define BUFFER_SIZE 2048

typedef	enum	e_length
{
	def,
	l,
	ll,
	h,
	hh
}				t_length;

typedef	struct	s_buffer
{
	char	content[BUFFER_SIZE];
	int		fd;
	size_t	size;
}				t_buffer;

typedef	struct	s_syntax
{
	t_bool		align_left;
	t_bool		plus;
	t_bool		space;
	t_bool		zero;
	t_bool		hash;
	int			width;
	int			precision;
	t_length	length;
	int			type;
	int			count;
}				t_syntax;

t_buffer		ft_buffinit(int fd);
void			ft_buffflush(t_buffer *buffer);
void			ft_buffcat(t_buffer *buffer, const char *s2, size_t size);
t_syntax		ft_parseflags(const char **format, t_syntax syntax);
t_syntax		ft_syntaxinit(void);
t_syntax		ft_parsewidth(const char **format, t_syntax syntax, va_list va);
t_syntax		ft_parseprecision(const char **f, t_syntax s, va_list va);
t_syntax		ft_parselength(const char **format, t_syntax syntax);
t_syntax		ft_parsetype(const char **format, t_syntax syntax);
t_syntax		ft_parsesyntax(const char **format, va_list va);
int				ft_def_conversion(t_syntax s, t_buffer *buff, va_list va);
int				ft_l_conversion(t_syntax syntax, t_buffer *buffer, va_list va);
int				ft_ll_conversion(t_syntax syntax, t_buffer *buffer, va_list va);
int				ft_h_conversion(t_syntax syntax, t_buffer *buffer, va_list va);
int				ft_hh_conversion(t_syntax syntax, t_buffer *buffer, va_list va);
int				ft_char_def(t_syntax syntax, t_buffer *buffer, va_list va);
int				ft_char_l(t_syntax syntax, t_buffer *buffer, va_list va);
int				ft_str_def(t_syntax syntax, t_buffer *buffer, va_list va);
int				ft_str_l(t_syntax syntax, t_buffer *buffer, va_list va);
int				ft_int_conv(t_syntax syntax, t_buffer *buffer, long long i);
int				ft_int_def(t_syntax syntax, t_buffer *buffer, va_list va);
int				ft_int_hh(t_syntax syntax, t_buffer *buffer, va_list va);
int				ft_int_h(t_syntax syntax, t_buffer *buffer, va_list va);
int				ft_int_l(t_syntax syntax, t_buffer *buffer, va_list va);
int				ft_int_ll(t_syntax syntax, t_buffer *buffer, va_list va);
int				ft_uint_conv(t_syntax s, t_buffer *buff,
		unsigned long long i);
int				ft_uhex_conv(t_syntax s, t_buffer *buf,
		unsigned	long	long i, t_bool upp);
int				ft_uint_def(t_syntax syntax, t_buffer *buffer, va_list va);
int				ft_uint_hh(t_syntax syntax, t_buffer *buffer, va_list va);
int				ft_uint_h(t_syntax syntax, t_buffer *buffer, va_list va);
int				ft_uint_l(t_syntax syntax, t_buffer *buffer, va_list va);
int				ft_uint_ll(t_syntax syntax, t_buffer *buffer, va_list va);
int				ft_uhex_def(t_syntax syntax, t_buffer *buffer, va_list va);
int				ft_uhex_ll(t_syntax syntax, t_buffer *buffer, va_list va);
int				ft_uhex_l(t_syntax syntax, t_buffer *buffer, va_list va);
int				ft_uhex_h(t_syntax syntax, t_buffer *buffer, va_list va);
int				ft_uhex_hh(t_syntax syntax, t_buffer *buffer, va_list va);
int				ft_ptr_def(t_syntax syntax, t_buffer *buffer, va_list va);
int				ft_prc_def(t_syntax syntax, t_buffer *buffer, va_list va);
int				ft_n_def(t_syntax syntax, t_buffer *buffer, va_list va);
int				ft_n_hh(t_syntax syntax, t_buffer *buffer, va_list va);
int				ft_n_h(t_syntax syntax, t_buffer *buffer, va_list va);
int				ft_n_ll(t_syntax syntax, t_buffer *buffer, va_list va);
int				ft_n_l(t_syntax syntax, t_buffer *buffer, va_list va);
void			ft_buff_fill(t_buffer *buffer, int c, int size);
int				ft_buffnbr_signed(long long si, char *bs, t_syntax s, char *b);
int				ft_buffnbr_unsigned(unsigned	long	long si,
		char *base, t_syntax s, char *buff);
int				ft_doconversion(t_syntax syntax, t_buffer *buffer, va_list va);
#endif
