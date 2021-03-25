/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wstring.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 16:22:08 by tmatis            #+#    #+#             */
/*   Updated: 2021/02/03 22:13:16 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WSTRING_H

# define WSTRING_H

# include <string.h>

int		ft_wstr_strlen(int *wstr);
size_t	ft_wstrlen(int *wstr);
size_t	ft_wstrnlen(const int *s, size_t maxlen);
size_t	ft_wstrtostr(char *dest, int *wsrc);
char	*ft_wstrtostr_malloc(int *wsrc);

#endif
