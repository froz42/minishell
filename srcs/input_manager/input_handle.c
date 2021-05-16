/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 12:42:21 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/16 17:08:10 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_manager.h"
#include <termios.h>

/*
** This is called when user type up key
*/

void	handle_up_key(t_buffer *buffer, int *history_fetch,
									char **temp, t_list *history)
{
	while (buffer->position)
	{
		ft_putstr(CURSOR_RIGHT);
		buffer->position--;
	}
	erase_x_chars(buffer->size);
	if (*history_fetch == -1)	// define genre "CURR_LINE" ?
		*temp = buffer->buff;
	else
		free(buffer->buff);
	if (*history_fetch < ft_lstsize(history) - 1)
		(*history_fetch)++;
	buffer->buff = ft_strdup(fetch_history(*history_fetch, history));
	if (!buffer->buff)
	{
		ft_log_error(strerror(errno));
		buffer->escape_id = EOT_ID;
		buffer->size = 0;
		return ;
	}
	buffer->size = ft_strlen(buffer->buff);
	ft_putstr(buffer->buff);
}

/*
** This is called when user type down key
*/

void	handle_down_key(t_buffer *buffer, int *history_fetch,
									char **temp, t_list *history)
{
	while (buffer->position)
	{
		ft_putstr(CURSOR_RIGHT);
		buffer->position--;
	}
	if (*history_fetch > -1)
		(*history_fetch)--;
	erase_x_chars(buffer->size);
	free(buffer->buff);
	if (*history_fetch == -1)
	{
		buffer->buff = *temp;
		*temp = NULL;
	}
	else if (*history_fetch != -1)
		buffer->buff = ft_strdup(fetch_history(*history_fetch, history));
	if (!buffer->buff)
	{
		ft_log_error(strerror(errno));
		buffer->escape_id = EOT_ID;
		buffer->size = 0;
		return ;
	}
	buffer->size = ft_strlen(buffer->buff);
	ft_putstr(buffer->buff);
}

/*
** This is called when user type left key
*/

void	handle_left_key(t_buffer *buffer)
{
	if (buffer->position < buffer->size)
	{
		ft_putstr(CURSOR_LEFT);
		buffer->position++;
	}
}

/*
** This is called when user type right key
*/

void	handle_right_key(t_buffer *buffer)
{
	if (buffer->position)
	{
		ft_putstr(CURSOR_RIGHT);
		buffer->position--;
	}
}

void	handle_ctrl_l(t_buffer *buffer)
{
	int	i;

	ft_putstr(CLEAR_SCREEN);
	print_prompt(buffer->status);
	ft_putstr(buffer->buff);
	i = 0;
	while (i < buffer->position)
	{
		ft_putstr(CURSOR_LEFT);
		i++;
	}
}
