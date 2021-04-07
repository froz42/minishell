/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 13:22:45 by tmatis            #+#    #+#             */
/*   Updated: 2021/04/07 21:24:01 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_manager.h"
#include <termios.h>


/*
** Erase one char on screen and buffer.
** TODO: do for a specific location for arrow left and right
*/

static int		handle_ctrl(t_buffer *buffer, int *history_fetch, char **temp, t_list **history)
{
	if (buffer->escape_id == 0 && buffer->size)
		erase_char(buffer);
	else if (buffer->escape_id == 1 && ft_lstsize(*history))
		handle_up_key(buffer, history_fetch, temp, *history);
	else if (buffer->escape_id == 2 && ft_lstsize(*history) && *temp)
		handle_down_key(buffer, history_fetch, temp, *history);
	else if (buffer->escape_id == 3)
		handle_right_key(buffer);
	else if (buffer->escape_id == 4)
		handle_left_key(buffer);
	else if (buffer->escape_id == 6)
		handle_ctrlc(buffer);
	else
		return (1);
	return (0);
}

static void		wait_line(char buff[10], t_buffer *buffer, char **temp, t_list **history)
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
				;//display_escape_code(buff, ret);
		}
		else
			buffer_add_chain(buff, ret, buffer);
	}
}

char	*get_input_line(t_list **history)
{
	char			*temp;
	t_buffer		buffer;
	char			buff[10];
	struct termios	old;

	buff[0] = 0;
	buffer = init_buffer();
	temp = NULL;
	old = raw_mode();
	wait_line(buff, &buffer, &temp, history);
	buff_mode(old);
	if (temp)
		free(temp);
	if (buffer.size > 0)
		push_history(ft_strdup(buffer.buff), history);

	return (buffer.buff);
}
