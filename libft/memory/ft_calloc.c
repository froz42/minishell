/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:36:17 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/17 12:32:35 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*dst;

	if (!count || !size)
	{
		size = 1;
		count = 1;
	}
	dst = malloc(size * count);
	if (dst)
		ft_bzero(dst, size * count);
	return (dst);
}

void	ft_safe_free(void *mem)
{
	if (mem)
		free(mem);
}
