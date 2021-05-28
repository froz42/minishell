/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 13:22:45 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/28 13:24:42 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_manager.h"
#include <termios.h>

/*
** Handle ctrl-chars and call the corresponding function
*/

static int	handle_ctrl_part2(t_buffer *buffer)
{
	if ((buffer->escape_id == LINE_START_ID && buffer->size)
		|| (buffer->escape_id == LINE_END_ID && buffer->pos_before_endl))
		handle_move_on_line(buffer);
	else if ((buffer->escape_id == CUT_LINE_END_ID && buffer->pos_before_endl)
		|| (buffer->escape_id == CUT_LINE_START_ID && buffer->size))
		handle_cut_line(buffer);
	else if (buffer->escape_id == WORD_LEFT_ID && buffer->size)
		handle_move_word_left(buffer);
	else if (buffer->escape_id == WORD_RIGHT_ID && buffer->pos_before_endl)
		handle_move_word_right(buffer);
	else if (buffer->escape_id == CUT_WORD_LEFT_ID && buffer->size)
		handle_cut_word_left(buffer);
	else if (buffer->escape_id == CUT_WORD_RIGHT_ID && buffer->pos_before_endl)
		handle_cut_word_right(buffer);
	else if (buffer->escape_id == PASTE_ID && buffer->clipboard)
		buffer_add_chain(buffer->clipboard,
			ft_strlen(buffer->clipboard), buffer);
	if (buffer->escape_id == EOT_ID && !buffer->size)
		return (handle_ctrl_d(buffer));
	return (0);
}

static int	handle_ctrl(t_buffer *buffer, char **save_curr_line,
									t_list **history)
{
	if (buffer->escape_id == DEL_ID && buffer->size)
		erase_char(buffer);
	else if (buffer->escape_id == SUPPR_ID && buffer->pos_before_endl)
	{
		handle_right_key(buffer);
		erase_char(buffer);
	}
	else if (buffer->escape_id == UP_KEY_ID && *history)
		handle_up_key(buffer, &buffer->history_lvl, save_curr_line, *history);
	else if (buffer->escape_id == DOWN_KEY_ID && *history && *save_curr_line)
		handle_down_key(buffer, &buffer->history_lvl, save_curr_line, *history);
	else if (buffer->escape_id == RIGHT_KEY_ID)
		handle_right_key(buffer);
	else if (buffer->escape_id == LEFT_KEY_ID)
		handle_left_key(buffer);
	else if (buffer->escape_id == ETX_ID)
		handle_ctrl_c(buffer);
	else if (buffer->escape_id == CLR_SCREEN_ID)
		handle_ctrl_l(buffer);
	return (handle_ctrl_part2(buffer));
}

/*
** Manage line waiting, buffering
*/

static int	wait_line(char buff[10], t_buffer *buffer,
						char **save_curr_line, t_list **history)
{
	int		ret;

	while (get_escape_id(buff, 0) != LF_ID)
	{
		ft_bzero(buff, 10);
		ret = read(STDIN_FILENO, buff, 10);
		if (buff[0] != LF && ft_iscntrl(buff[0]) && ret != -1)
		{
			buffer_add(LF, buffer);
			buffer->escape_id = get_escape_id(buff, ret);
			if (handle_ctrl(buffer, save_curr_line, history) == EOT)
				return (false);
		}
		else if (ret != -1)
			buffer_add_chain(buff, ret, buffer);
		if (ret == -1)
		{
			ft_log_error(strerror(errno));
			handle_ctrl_d(buffer);
		}
		if (buffer->error || ret == -1)
			return (false);
	}
	return (true);
}

/*
** similar working as get_next_line, read from STDIN_FILENO, handle ctrl-char
*/

int	get_input_line(char **line, char **clipboard,
							t_list **history, char *status)
{
	char			buff[10];
	t_buffer		buffer;
	char			*save_curr_line;
	struct termios	old_termios;
	int				ret;

	ft_bzero(buff, 10);
	buffer = init_buffer(*clipboard, status);
	save_curr_line = NULL;
	old_termios = raw_mode();
	print_prompt(status);
	ret = wait_line(buff, &buffer, &save_curr_line, history);
	buff_mode(old_termios);
	if (save_curr_line)
		free(save_curr_line);
	if (buffer.size > 0 && buffer.buff)
		push_history(ft_strdup(buffer.buff), history);
	*line = buffer.buff;
	*clipboard = buffer.clipboard;
	return (ret);
}
