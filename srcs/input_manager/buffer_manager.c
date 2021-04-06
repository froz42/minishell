/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 12:53:58 by tmatis            #+#    #+#             */
/*   Updated: 2021/04/06 12:47:06 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_manager.h"

/*
** Init my structure
*/

t_buffer	init_buffer(void)
{
	t_buffer buffer;

	buffer.size = 0;
	buffer.buff = malloc(sizeof(char));
	buffer.buff[0] = '\0';
	buffer.escape_id= -1;
	return (buffer);
}

/*
** Add a char to a static buff, if buff is full or \n is typed
** flushed to a HEAP allocated buffer
*/

void	buffer_add(char c, t_buffer *buffer)
{
	static char		buff[10];
	static int		buff_size = 0;
	char			*dst;

	if ((c == 10 && (buff_size > 0 || !buffer->buff))
			|| (&buff[buff_size] == &buff[sizeof(buff)]))
	{
		dst = ft_calloc(buff_size + buffer->size + 1, sizeof(char));
		if (!dst)
		{
			ft_log_error(strerror(errno));
			return ;
		}
		ft_memcpy(dst, buffer->buff, buffer->size);
		ft_memcpy(dst + buffer->size, buff, buff_size);
		buffer->size += buff_size;
		buff_size = 0;
		if (buffer->buff)
			free(buffer->buff);
		buffer->buff = dst;
	}
	if (c != 10)
		buff[buff_size++] = c;
}

/*
** Add a chain of char of size size 
*/

void	buffer_add_chain(char *src, int size, t_buffer *buffer)
{
	int	i;

	i = 0;
	while (i < size)
		buffer_add(src[i++], buffer);
}

/*
** Move all byte to left after the pos one to erase a char.
** Add a \0 at the end
*/

void	buffer_delete(int pos, t_buffer *buffer)
{
	ft_memmove(buffer + pos, buffer + (pos - 1), buffer->size - pos);
	buffer->buff[--buffer->size] = '\0';
}
