/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 12:42:21 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/27 18:37:06 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_manager.h"
#include <termios.h>

/*
** This is called when user type up key
*/

void	handle_up_key(t_buffer *buffer, int *history_lvl,
									char **temp, t_list *history)
{
	while (buffer->pos_before_endl)
	{
		ft_putstr(CURSOR_RIGHT);
		buffer->pos_before_endl--;
	}
	erase_x_chars(buffer->size);
	if (*history_lvl == -1)
		*temp = buffer->buff;
	else
		free(buffer->buff);
	if (*history_lvl < ft_lstsize(history) - 1)
		(*history_lvl)++;
	buffer->buff = ft_strdup(fetch_history(*history_lvl, history));
	return (handle_eot_error(buffer));
}

/*
** This is called when user type down key
*/

void	handle_down_key(t_buffer *buffer, int *history_lvl,
									char **temp, t_list *history)
{
	while (buffer->pos_before_endl)
	{
		ft_putstr(CURSOR_RIGHT);
		buffer->pos_before_endl--;
	}
	if (*history_lvl > -1)
		(*history_lvl)--;
	erase_x_chars(buffer->size);
	free(buffer->buff);
	if (*history_lvl == -1)
	{
		buffer->buff = *temp;
		*temp = NULL;
	}
	else
		buffer->buff = ft_strdup(fetch_history(*history_lvl, history));
	return (handle_eot_error(buffer));
}

/*
** This is called when user type left key
*/

void	handle_left_key(t_buffer *buffer)
{
	if (buffer->pos_before_endl < buffer->size)
	{
		ft_putstr(CURSOR_LEFT);
		buffer->pos_before_endl++;
	}
}

/*
** This is called when user type right key
*/

void	handle_right_key(t_buffer *buffer)
{
	if (buffer->pos_before_endl)
	{
		ft_putstr(CURSOR_RIGHT);
		buffer->pos_before_endl--;
	}
}

void	handle_ctrl_l(t_buffer *buffer)
{
	int	i;

	ft_putstr(CLEAR_SCREEN);
	print_prompt(buffer->status);
	ft_putstr(buffer->buff);
	i = 0;
	while (i < buffer->pos_before_endl)
	{
		ft_putstr(CURSOR_LEFT);
		i++;
	}
}
