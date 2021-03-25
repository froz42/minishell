/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 20:24:49 by tmatis            #+#    #+#             */
/*   Updated: 2021/01/04 16:31:51 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

char	*ft_strrchr(const char *s, int c)
{
	char	cc;
	char	*save;

	save = NULL;
	cc = (char)c;
	while (1)
	{
		if (*s == cc)
			save = (char *)s;
		if (!*s)
			return (save);
		s++;
	}
}
