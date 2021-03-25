/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrtostr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 20:51:21 by tmatis            #+#    #+#             */
/*   Updated: 2021/01/04 16:28:57 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wstring.h"
#include "../memory/memory.h"
#include "../char/char.h"
#include <stdlib.h>

size_t	ft_wstrtostr(char *dest, int *wsrc)
{
	char	buff[4];
	size_t	i;
	size_t	len;
	int		buffed;

	i = 0;
	len = 0;
	while (wsrc[i])
	{
		buffed = ft_utf8_encode(wsrc[i++], buff);
		ft_memcpy(dest + len, buff, buffed);
		len += buffed;
	}
	dest[len++] = '\0';
	return (len);
}

char	*ft_wstrtostr_malloc(int *wsrc)
{
	char	buff[4];
	size_t	i;
	size_t	len;
	int		buffed;
	char	*dest;

	i = 0;
	len = 0;
	dest = (char *)malloc(sizeof(char));
	while (wsrc[i])
	{
		buffed = ft_utf8_encode(wsrc[i++], buff);
		dest = ft_realloc(dest, len, buffed);
		ft_memcpy(dest + len, buff, buffed);
		len += buffed;
	}
	dest[len++] = '\0';
	return (dest);
}
