/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:09:20 by tmatis            #+#    #+#             */
/*   Updated: 2021/01/11 18:41:13 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHAR_H

# define CHAR_H

int	ft_isalnum(int c);
int	ft_isalpha(int c);
int	ft_isascii(int c);
int	ft_isdigit(int c);
int	ft_islower(int c);
int	ft_isprint(int c);
int	ft_isupper(int c);
int	ft_tolower(int c);
int	ft_toupper(int c);
int	ft_utf8_encode(int c, char *buff);
int	ft_isspace(int c);
int	ft_isnum(int c);

#endif
