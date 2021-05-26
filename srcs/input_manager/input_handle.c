/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 12:42:21 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/26 17:43:43 by jmazoyer         ###   ########.fr       */
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

#include <sys/ioctl.h> // mettre ailleurs

typedef struct	s_screen_coord
{
	int		line;
	int		col;
}				t_screen_coord;

void	get_coord(t_screen_coord *screen, t_screen_coord *cursor)
{
	struct winsize	win_size;
	char			buffer[64];

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &win_size))
		ft_log_error(strerror(errno));
	screen->line = win_size.ws_row;
	screen->col = win_size.ws_col;
	ft_putstr("\033[6n");
	if (read(STDIN_FILENO, buffer, sizeof(buffer)) == -1)
		ft_log_error("Problem while reading cursor coordinates from stdin");
	cursor->line = ft_atoi(&buffer[2]);
	cursor->col = ft_atoi(&buffer[5]);
}

void	handle_left_key(t_buffer *buffer)
{
	t_screen_coord	screen;
	t_screen_coord	cursor;

	get_coord(&screen, &cursor);
	printf("screen line = %d, screen_col = %d\ncursor_line = %d, cursor_col = %d\n", screen.line, screen.col, cursor.line, cursor.col);
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
	struct winsize	ws;

	ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
	printf ("lines %d\n", ws.ws_row);
	printf ("columns %d\n", ws.ws_col);

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
