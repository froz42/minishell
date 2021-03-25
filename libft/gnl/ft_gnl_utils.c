/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 15:02:17 by tmatis            #+#    #+#             */
/*   Updated: 2021/02/03 21:56:15 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_gnl.h"

int		ft_getendl(t_chunk *chunk)
{
	int		i;

	i = 0;
	while (i < chunk->len)
	{
		if (chunk->data[i] == '\n' || chunk->data[i] == '\0')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_extractstr(t_chunk *chunk, int size)
{
	char	*dest;
	int		i;

	dest = (char *)malloc((size + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (size--)
	{
		dest[i] = chunk->data[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

t_chunk	*ft_rallocut(t_chunk *chunk, int start)
{
	char	*dest;
	int		len;
	int		i;

	len = chunk->len - start;
	dest = (char *)malloc((len) * sizeof(char));
	if (!dest)
	{
		free(chunk->data);
		return (NULL);
	}
	i = 0;
	while (start < chunk->len)
		dest[i++] = chunk->data[start++];
	free(chunk->data);
	chunk->len = len;
	chunk->data = dest;
	return (chunk);
}

t_chunk	*ft_rallocat(t_chunk *chunk, char *data, int len)
{
	char	*dest;
	int		i;

	dest = (char *)malloc((chunk->len + len) * sizeof(char));
	if (!dest)
	{
		free(chunk->data);
		return (NULL);
	}
	i = 0;
	while (i < chunk->len)
	{
		dest[i] = chunk->data[i];
		i++;
	}
	while (i < (chunk->len + len))
		dest[i++] = *data++;
	free(chunk->data);
	chunk->len = chunk->len + len;
	chunk->data = dest;
	return (chunk);
}

void	ft_initchunk(t_chunk *chunk)
{
	chunk->init = 1;
	chunk->data = malloc(sizeof(char));
	chunk->len = 0;
}
