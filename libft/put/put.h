/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:52:25 by tmatis            #+#    #+#             */
/*   Updated: 2021/04/22 12:57:48 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUT_H

# define PUT_H
# include "../string/string.h"

void	ft_putchar_fd(int c, int fd);
void	ft_putwstr_fd(int *wstr, int fd);
void	ft_putstr(char *str);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putchar_fd(int c, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putnl(char *str);
void	ft_putprintable(char *str);

#endif
