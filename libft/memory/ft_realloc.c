/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 12:09:06 by tmatis            #+#    #+#             */
/*   Updated: 2021/01/08 21:19:55 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"
#include <stdlib.h>

void	*ft_realloc(void *src, size_t size, size_t addbyte)
{
	char	*csrc;
	char	*cdest;

	csrc = (char *)src;
	cdest = (char *)malloc((size + addbyte) * sizeof(char));
	ft_memcpy(cdest, csrc, size);
	free(src);
	return ((void *)cdest);
}
