/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handle3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 13:19:57 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/28 13:28:33 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_manager.h"

void	handle_cut_line(t_buffer *buffer)
{
	int		i;

	i = buffer->size - buffer->pos_before_endl;
	if (buffer->escape_id == CUT_LINE_START_ID && i == 0)
		return ;
	ft_safe_free(buffer->clipboard);
	if (buffer->escape_id == CUT_LINE_START_ID)
		buffer->clipboard = ft_substr(buffer->buff, 0, i);
	else
		buffer->clipboard = ft_substr(buffer->buff, i, buffer->pos_before_endl);
	if (!buffer->clipboard)
		return (eot_error(buffer));
	if (buffer->escape_id == CUT_LINE_START_ID)
		while (i--)
			erase_char(buffer);
	else
	{
		while (buffer->pos_before_endl)
		{
			handle_right_key(buffer);
			erase_char(buffer);
		}
	}
}

void	handle_move_word_left(t_buffer *buffer)
{
	int		i;

	i = buffer->size - buffer->pos_before_endl;
	while (buffer->pos_before_endl < buffer->size
		&& !ft_isalnum(buffer->buff[i - 1]))
	{
		handle_left_key(buffer);
		i--;
	}
	while (buffer->pos_before_endl < buffer->size
		&& ft_isalnum(buffer->buff[i - 1]))
	{
		handle_left_key(buffer);
		i--;
	}
}

void	handle_move_word_right(t_buffer *buffer)
{
	int		i;

	i = buffer->size - buffer->pos_before_endl;
	while (buffer->pos_before_endl > 0 && !ft_isalnum(buffer->buff[i]))
	{
		handle_right_key(buffer);
		i++;
	}
	while (buffer->pos_before_endl > 0 && ft_isalnum(buffer->buff[i]))
	{
		handle_right_key(buffer);
		i++;
	}
}

void	handle_cut_word_left(t_buffer *buffer)
{
	int		i;
	int		old_pos_before_endl;

	i = buffer->size - buffer->pos_before_endl;
	if (i == 0)
		return ;
	old_pos_before_endl = buffer->pos_before_endl;
	handle_move_word_left(buffer);
	ft_safe_free(buffer->clipboard);
	i = buffer->pos_before_endl - old_pos_before_endl;
	buffer->clipboard = ft_substr(buffer->buff,
			buffer->size - buffer->pos_before_endl, i);
	if (!buffer->clipboard)
		return (eot_error(buffer));
	while (i--)
	{
		handle_right_key(buffer);
		erase_char(buffer);
	}
}

void	handle_cut_word_right(t_buffer *buffer)
{
	int		i;
	int		old_pos_before_endl;

	i = buffer->size - buffer->pos_before_endl;
	old_pos_before_endl = buffer->pos_before_endl;
	handle_move_word_right(buffer);
	ft_safe_free(buffer->clipboard);
	buffer->clipboard = ft_substr(buffer->buff, i,
			old_pos_before_endl - buffer->pos_before_endl);
	if (!buffer->clipboard)
		return (eot_error(buffer));
	i = old_pos_before_endl - buffer->pos_before_endl;
	while (i--)
		erase_char(buffer);
}
