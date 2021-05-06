/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 13:22:45 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/06 12:35:26 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_manager.h"
#include <termios.h>

/*
** Print the prompt
*/

void	print_prompt(void)
{
	ft_putstr("\x1B[32m");
	ft_putstr(getenv("USER"));
	ft_putstr("\x1B[37m");
	ft_putstr("@");
	ft_putstr("\x1B[34m");
	ft_putstr("minishell");
	ft_putstr("\x1B[37m");
	ft_putstr("$ ");
	ft_putstr("\x1B[0m");
}

/*
** Handle ctrl chars and call the right function
*/

static int	handle_ctrl(t_buffer *buffer, int *history_fetch,
				char **temp, t_list **history)
{
	if (buffer->escape_id == 0 && buffer->size)
		erase_char(buffer);
	else if (buffer->escape_id == 1 && buffer->manage_history
		&& ft_lstsize(*history))
		handle_up_key(buffer, history_fetch, temp, *history);
	else if (buffer->escape_id == 2 && buffer->manage_history
		&& ft_lstsize(*history) && *temp)
		handle_down_key(buffer, history_fetch, temp, *history);
	else if (buffer->escape_id == 3)
		handle_right_key(buffer);
	else if (buffer->escape_id == 4)
		handle_left_key(buffer);
	else if (buffer->escape_id == 6)
		handle_ctrlc(buffer);
	else if (buffer->escape_id == 7 && !buffer->size)
	{
		handle_ctrld(buffer);
		return (1);
	}
	return (0);
}

/*
** Manage line waiting, buffering
*/

static int	wait_line(char buff[10], t_buffer *buffer,
				char **temp, t_list **history)
{
	int		ret;
	int		history_fetch;

	history_fetch = -1;
	while (get_escape_id(buff, 0) != 5)
	{
		ret = read(STDIN_FILENO, buff, 10);
		if (buff[0] != 10 && ft_iscntrl(buff[0]))
		{
			buffer_add(10, buffer);
			buffer->escape_id = get_escape_id(buff, ret);
			if (handle_ctrl(buffer, &history_fetch, temp, history))
				return (0);
		}
		else
			buffer_add_chain(buff, ret, buffer);
	}
	return (1);
}

/*
** similar working as get_next_line, read from STDIN_FILENO, handle ctrl char
*/

int	get_input_line(char **line, t_bool manage_history,
		t_list **history)
{
	char			*temp;
	t_buffer		buffer;
	char			buff[10];
	struct termios	old;
	int				ret;

	buff[0] = 0;
	buffer = init_buffer(manage_history);
	temp = NULL;
	old = raw_mode();
	ret = wait_line(buff, &buffer, &temp, history);
	buff_mode(old);
	if (temp)
		free(temp);
	if (buffer.size > 0)
		push_history(ft_strdup(buffer.buff), history);
	*line = buffer.buff;
	return (ret);
}
