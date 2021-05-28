/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 21:19:47 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/28 13:32:41 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_manager.h"
#include <termios.h>

/*
** Set terminal in raw mode (char by char)
*/

struct termios	raw_mode(void)
{
	struct termios	termios;
	struct termios	old_termios;

	tcgetattr(STDIN_FILENO, &termios);
	old_termios = termios;
	termios.c_lflag &= ~(ECHO | ICANON | ISIG);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios);
	return (old_termios);
}

/*
** Set terminal in buff mode (line by line)
*/

void	buff_mode(struct termios old_termios)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &old_termios);
}

/*
** Replace x chars with space.
*/

void	erase_x_chars(int x)
{
	while (x--)
		ft_putstr("\b \b");
}

void	eot_error(t_buffer *buffer)
{
	ft_log_error(strerror(errno));
	buffer->escape_id = EOT_ID;
	buffer->size = 0;
}

void	handle_eot_error(t_buffer *buffer)
{
	if (!buffer->buff)
		return (eot_error(buffer));
	buffer->size = ft_strlen(buffer->buff);
	ft_putstr(buffer->buff);
}
