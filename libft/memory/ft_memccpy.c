/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 18:16:56 by tmatis            #+#    #+#             */
/*   Updated: 2021/01/04 15:33:45 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	i;
	char	*s1;
	char	*s2;

	s1 = (char *)dst;
	s2 = (char *)src;
	i = 0;
	while (i < n && s2[i] != (char)c)
	{
		s1[i] = s2[i];
		i++;
	}
	if (i == n)
		return (NULL);
	s1[i++] = (char)c;
	return (&s1[i]);
}
