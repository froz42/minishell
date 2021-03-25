/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 12:13:02 by tmatis            #+#    #+#             */
/*   Updated: 2021/01/04 16:31:43 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	cut;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	cut = ft_strlen(s1);
	while (cut && ft_strchr(set, s1[cut]))
		cut--;
	return (ft_substr(s1, 0, cut + 1));
}
