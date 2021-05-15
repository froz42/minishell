/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 13:22:45 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/15 22:52:58 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_manager.h"
#include <termios.h>

static char	*get_last_dir(void)
{
	char	actual_dir[BUFFER_SIZE];
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

static int	handle_ctrl(t_buffer *buffer, int *history_fetch,
									char **temp, t_list **history)
{
	if (buffer->escape_id == DEL_ID && buffer->size)
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
		handle_ctrl_c(buffer);
	else if (buffer->escape_id == EOT_ID && !buffer->size)
	{
		handle_ctrl_d(buffer);
		return (EOT);
	}
	else if (buffer->escape_id == 8)
		handle_ctrl_l(buffer);
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
	while (get_escape_id(buff, 0) != LF_ID)
	{
		ret = read(STDIN_FILENO, buff, 10);	// protect against read error
		if (buff[0] != LF && ft_iscntrl(buff[0]))
		{
			buffer_add(LF, buffer);
			buffer->escape_id = get_escape_id(buff, ret);
			if (handle_ctrl(buffer, &history_fetch, temp, history) == EOT)
				return (0);	// rename return via define
		}
		else
			buffer_add_chain(buff, ret, buffer);
	}
	return (1);	// rename return via define
}

/*
** similar working as get_next_line, read from STDIN_FILENO, handle ctrl char
*/

int	get_input_line(char **line, t_bool manage_history,
							t_list **history, char *status)
{
	char			buff[10];
	t_buffer		buffer;
	char			*temp;
	struct termios	old_termios;
	int				ret;

	buff[0] = '\0';
	buffer = init_buffer(manage_history, status);
	temp = NULL;
	old_termios = raw_mode();
	print_prompt(status);
	ret = wait_line(buff, &buffer, &temp, history);
	buff_mode(old_termios);
	if (temp)
		free(temp);
	if (buffer.size > 0)
		push_history(ft_strdup(buffer.buff), history);
	*line = buffer.buff;
	return (ret);
}
