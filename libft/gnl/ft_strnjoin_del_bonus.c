/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin_del_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmazoyer <jmazoyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 17:05:21 by jmazoyer          #+#    #+#             */
/*   Updated: 2021/05/17 14:52:16 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft.h"

static void	delete(char *s1, char *s2, int to_del)
{
	if (s1 && (to_del == 1 || to_del == 3))
		free(s1);
	if (s2 && (to_del == 2 || to_del == 3))
		free(s2);
}

char		*ft_strnjoin_del(char *s1, char *s2, size_t n, int to_del)
{
	char	*dst;
	size_t	size;
	size_t	i;
	size_t	j;

	size = 0;
	if (s1)
		size += ft_strlen(s1);
	if (s2)
		size += ft_min_size_t(n, ft_strlen(s2));
	if ((dst = (char *)malloc((size + 1) * sizeof(char))) == NULL)
	{
		delete(s1, s2, to_del);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (s1 && s1[j])
		dst[i++] = s1[j++];
	j = 0;
	while (s2 && s2[j] && n-- > 0)
		dst[i++] = s2[j++];
	dst[size] = '\0';
	delete(s1, s2, to_del);
	return (dst);
}
