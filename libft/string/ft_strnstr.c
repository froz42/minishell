/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 22:53:10 by tmatis            #+#    #+#             */
/*   Updated: 2021/01/04 16:32:03 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	nlen;

	nlen = ft_strlen(needle);
	if (nlen == 0)
		return ((char *)haystack);
	while (*haystack && ft_strncmp(haystack, needle, nlen) != 0 && len > nlen)
	{
		haystack++;
		len--;
	}
	if (ft_strncmp(haystack, needle, nlen) == 0)
		return ((char *)haystack);
	return (NULL);
}
