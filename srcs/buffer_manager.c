/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 12:53:58 by tmatis            #+#    #+#             */
/*   Updated: 2021/03/29 22:10:34 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

t_buffer	init_buffer(void)
{
	t_buffer buffer;

	buffer.size = 0;
	buffer.buff = NULL;
	return (buffer);
}

void	buffer_add(char c, t_buffer *buffer)
{
	static char		buff[10];
	static int		buff_size = 0;
	char			*dst;

	if (c == 10 || (&buff[buff_size] == &buff[sizeof(buff)]))
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
