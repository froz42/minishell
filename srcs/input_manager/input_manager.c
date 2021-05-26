/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 13:22:45 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/26 12:01:30 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_manager.h"
#include <termios.h>

static char	*get_last_dir(void)
{
	char	actual_dir[4098];
	char	**split;
	int		i;
	char	*last_dir;

	getcwd(actual_dir, sizeof(actual_dir));
	split = ft_split(actual_dir, '/');
	if (!split)
		return (NULL);
	i = 0;
	while (split[i])
		i++;
	if (i > 0)
		last_dir = ft_strdup(split[i - 1]);
	else
		return (ft_strdup("/"));
	free_table(&split);
	return (last_dir);
}

/*
** Print the prompt
*/

void	print_prompt(char *status)
{
	char	*user;
	char	*last_dir;

	user = getenv("USER");
	ft_putstr("\x1B[32m");
	if (user)
		ft_putstr(user);
	ft_putstr("\x1B[37m@");
	ft_putstr("\x1B[34mminishell");
	last_dir = get_last_dir();
	if (last_dir)
	{
		ft_putstr("\x1B[37m (\x1B[33m");
		ft_putstr(last_dir);
		free(last_dir);
		ft_putstr("\x1B[37m)");
	}
	ft_putstr(" (");
	if (ft_atoi(status) > 0)
		ft_putstr("\x1B[31m");
	else
		ft_putstr("\x1B[32m");
	ft_putstr(status);
	ft_putstr("\x1B[0m)");
	ft_putstr("$ ");
}

/*
** Handle ctrl-chars and call the corresponding function
*/

void	handle_move_on_line(t_buffer *buffer)
{
	if (buffer->escape_id == LINE_START_ID)
	{
		while (buffer->pos_before_endl < buffer->size)
			handle_left_key(buffer);
		return ;
	}
	while (buffer->pos_before_endl > 0)
		handle_right_key(buffer);
}

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
		while (buffer->pos_before_endl)
		{
			handle_right_key(buffer);
			erase_char(buffer);
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
	if (buffer->escape_id == EOT_ID && !buffer->size)
		return (handle_ctrl_d(buffer));
	return (0);
}

static int	handle_ctrl(t_buffer *buffer, char **save_curr_line,
									t_list **history)
{
	if (buffer->escape_id == DEL_ID && buffer->size)
		erase_char(buffer);
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
