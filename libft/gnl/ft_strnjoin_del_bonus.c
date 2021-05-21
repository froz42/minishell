/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin_del_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 17:05:21 by jmazoyer          #+#    #+#             */
/*   Updated: 2021/05/21 00:00:00 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft.h"

void	set_value(char *s1, char *s2, char *strs[2])
{
	strs[0] = s1;
	strs[1] = s2;
}

char	*ft_strnjoin_del(char *s1, char *s2, size_t n, int to_del)
{
	char	*dst;
	size_t	size;
	size_t	i;
	size_t	j;
	char	*strs[2];

	size = 0;
	if (s1)
		size += ft_strlen(s1);
	if (s2)
		size += ft_min_size_t(n, ft_strlen(s2));
	set_value(s1, s2, strs);
	dst = compute_first_part(size, strs, to_del, &i);
	if (!dst)
		return (NULL);
	j = 0;
	while (s2 && s2[j] && n-- > 0)
		dst[i++] = s2[j++];
	dst[size] = '\0';
	delete_gnl(s1, s2, to_del);
	return (dst);
}
