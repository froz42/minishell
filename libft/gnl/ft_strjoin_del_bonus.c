/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_del_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 17:04:54 by jmazoyer          #+#    #+#             */
/*   Updated: 2021/05/20 23:58:51 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft.h"

void	delete_gnl(char *s1, char *s2, int to_del)
{
	if (s1 && (to_del == 1 || to_del == 3))
		free(s1);
	if (s2 && (to_del == 2 || to_del == 3))
		free(s2);
}

char	*compute_first_part(size_t size, char *strs[2], int to_del, size_t *i)
{
	char	*dst;
	size_t	j;

	dst = (char *)malloc((size + 1) * sizeof(char));
	if (dst == NULL)
	{
		delete_gnl(strs[0], strs[1], to_del);
		return (NULL);
	}
	*i = 0;
	j = 0;
	while (strs[0] && strs[0][j])
		dst[(*i)++] = strs[0][j++];
	return (dst);
}

char	*ft_strjoin_del(char *s1, char *s2, int to_del)
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
		size += ft_strlen(s2);
	set_value(s1, s2, strs);
	dst = compute_first_part(size, strs, to_del, &i);
	if (!dst)
		return (NULL);
	j = 0;
	while (s2 && s2[j])
		dst[i++] = s2[j++];
	dst[size] = '\0';
	delete_gnl(s1, s2, to_del);
	return (dst);
}
