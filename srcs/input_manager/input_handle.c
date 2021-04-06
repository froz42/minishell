/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 12:42:21 by tmatis            #+#    #+#             */
/*   Updated: 2021/04/06 13:21:20 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_manager.h"
#include <termios.h>

void		 handle_up_key(t_buffer *buffer, int *history_fetch, char **temp, t_list *history)
{
	erase_x_chars(buffer->size);
	if (*history_fetch == -1)
		*temp = buffer->buff;
	else
		free(buffer->buff);
	if (*history_fetch < ft_lstsize(history) - 1)
		(*history_fetch)++;
	buffer->buff = ft_strdup(fetch_history(*history_fetch, history));
	buffer->size = ft_strlen(buffer->buff);
	ft_putstr(buffer->buff);
}

void		handle_down_key(t_buffer *buffer, int *history_fetch, char **temp, t_list *history)
{
	if (*history_fetch > -1)
		(*history_fetch)--;
	erase_x_chars(buffer->size);
	free(buffer->buff);
	if (*history_fetch == -1 && temp)
	{
		buffer->buff = *temp;
		*temp = NULL;
	}
	else if (*history_fetch != -1)
		buffer->buff = ft_strdup(fetch_history(*history_fetch, history));
	buffer->size = ft_strlen(buffer->buff);
	ft_putstr(buffer->buff);
}

void		erase_char(t_buffer *buffer)
{
	erase_x_chars(1);
	buffer_delete(buffer->size, buffer);
}
