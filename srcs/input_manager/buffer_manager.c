/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 12:53:58 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/16 23:15:40 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_manager.h"


/*
** Init my structure
*/

t_buffer	init_buffer(t_bool manage_history, char *status)
{
	t_buffer	buffer;

	buffer.size = 0;
	buffer.position = 0;
	buffer.buff = malloc(sizeof(char));
	buffer.buff[0] = '\0';
	buffer.escape_id = -1;
	buffer.manage_history = manage_history;
	buffer.status = status;
	return (buffer);
}

/*
** Add a char to a static buff, if buff is full or \n is typed
** flushed to a HEAP allocated buffer
*/

void	buffer_add(char c, t_buffer *buffer)
{
	static char		buff[10];
	static int		i = 0;
	char			*dst;

	if ((c == LF && (i > 0 || !buffer->buff))
		|| (&buff[i] == &buff[sizeof(buff)]))
	{
		if (i != 5)
			dst = ft_calloc(i + buffer->size + 1, sizeof(char));
		else
			dst = NULL;
//		dst = ft_calloc(i + buffer->size + 1, sizeof(char));
		if (!dst)	// re-afficher le prompt d'avant erreur ?
		{
			ft_log_error(strerror(errno));
			return ;
		}
		ft_memcpy(dst, buffer->buff, buffer->size);
		ft_memcpy(dst + buffer->size, buff, i);
		buffer->size += i;
		i = 0;
		if (buffer->buff)
			free(buffer->buff);
		buffer->buff = dst;
	}
	if (c != LF)
		buff[i++] = c;
}

/*
** Add a char at a specific position
*/

void	buffer_add_pos(char c, int pos, t_buffer *buffer)
{
	char	*dst;

	buffer_add(LF, buffer);
	dst = ft_calloc(buffer->size + 2, sizeof(char));
	if (!dst)
	{
		ft_log_error(strerror(errno));
		buffer->size = 0;
		buffer->escape_id = handle_ctrl_d(buffer);
		return ;
	}
	ft_memcpy(dst, buffer->buff, pos);
	dst[pos] = c;
	ft_memcpy(dst + pos + 1, buffer->buff + pos, buffer->size - pos);
	buffer->size++;
	if (buffer->buff)
		free(buffer->buff);
	buffer->buff = dst;
}

/*
** Add a chain of char of size size
*/

void	buffer_add_chain(char *src, int size, t_buffer *buffer)
{
	int	i;

	write(STDOUT_FILENO, src, size);
	if (src[0] != LF && buffer->position)
	{
		buffer_add(LF, buffer);
		ft_putstr(buffer->buff + (buffer->size - buffer->position));
		i = 0;
		while (i++ < buffer->position)
			ft_putstr(CURSOR_LEFT);
		i = 0;
		while (i < size)
			buffer_add_pos(src[i++], buffer->size - buffer->position, buffer);
	}
	else
	{
		i = 0;
		while (i < size)
			buffer_add(src[i++], buffer);
	}
}

/*
** Move all byte to left after the pos one to erase a char.
** Add a \0 at the end
*/

void	buffer_delete(int pos, t_buffer *buffer)
{
	ft_memmove(buffer->buff + (pos - 1),
		buffer->buff + pos, buffer->size - pos);
	buffer->buff[--buffer->size] = '\0';
}
