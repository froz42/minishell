/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 13:22:45 by tmatis            #+#    #+#             */
/*   Updated: 2021/04/05 21:24:50 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_manager.h"
#include <termios.h>


static void		 handle_up_key(t_buffer *buffer, int *history_fetch, char **temp, t_list *history)
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

static void		handle_down_key(t_buffer *buffer, int *history_fetch, char **temp, t_list *history)
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

/*
** Erase one char on screen and buffer.
** TODO: do for a specific location for arrow left and right
*/

static void		erase_char(t_buffer *buffer)
{
	erase_x_chars(1);
	buffer_delete(buffer->size, buffer);
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
			if (get_escape_id(buff, ret) == 0 && buffer->size)
				erase_char(buffer);
			else if (get_escape_id(buff, ret) == 1 && ft_lstsize(*history))
				handle_up_key(buffer, &history_fetch, temp, *history);
			else if (get_escape_id(buff, ret) == 2 && ft_lstsize(*history) && *temp)
				handle_down_key(buffer, &history_fetch, temp, *history);
		}
		else
		{
			buffer_add_chain(buff, ret, buffer);
			write(1, buff, ret);
		}
	}
}

char	*get_input_line(t_list **history)
{
	char			*temp;
	t_buffer		buffer;
	char			buff[10];

	buff[0] = 0;
	buffer = init_buffer();
	temp = NULL;
	raw_mode();
	wait_line(buff, &buffer, &temp, history);
	buff_mode();
	if (temp)
		free(temp);
	if (buffer.size > 0)
		push_history(ft_strdup(buffer.buff), history);
	return (buffer.buff);
}
