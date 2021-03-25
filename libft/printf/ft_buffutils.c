/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buffutils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:22:13 by tmatis            #+#    #+#             */
/*   Updated: 2021/02/03 22:10:09 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

t_buffer	ft_buffinit(int fd)
{
	t_buffer	buff;

	buff.size = 0;
	buff.fd = fd;
	return (buff);
}

void		ft_buffflush(t_buffer *buffer)
{
	write(buffer->fd, buffer->content, buffer->size);
	buffer->size = 0;
}

void		ft_buffcat(t_buffer *buffer, const char *s2, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (&buffer->content[buffer->size] == &buffer->content[BUFFER_SIZE])
			ft_buffflush(buffer);
		buffer->content[buffer->size++] = s2[i];
		i++;
	}
}

void		ft_buff_fill(t_buffer *buffer, int c, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (&buffer->content[buffer->size] == &buffer->content[BUFFER_SIZE])
			ft_buffflush(buffer);
		buffer->content[buffer->size++] = (char)c;
		i++;
	}
}
