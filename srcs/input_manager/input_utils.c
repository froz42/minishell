/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 21:19:47 by tmatis            #+#    #+#             */
/*   Updated: 2021/04/06 13:24:33 by tmatis           ###   ########.fr       */
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
	struct termios	old;

	tcgetattr(STDIN_FILENO, &termios);
	old = termios;
	termios.c_lflag &= ~(ECHO | ICANON | ISIG);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios);
	return (old);
}

/*
** Set terminal in buff mode (line by line)
*/

void			buff_mode(struct termios old)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &old);
}

/*
** Replace x chars with space.
*/

void		erase_x_chars(int x)
{
	while (x--)
		ft_putstr("\b \b");
}

/*
** Return an id from an escape sequence
** DEL -> 0
** ARROW_UP -> 1
** ARROW_DOWN -> 2
** ARROW_RIGHT -> 3
** ARROW_LEFT -> 4
** RETURN -> 5
** CTRL-C -> 6
*/

int			get_escape_id(char *buff, int size)
{
	if (buff[0] == 0177)
		return (0);
	if (size == 3 && !ft_memcmp(buff, "\33\133\101", 3))
		return (1);
	if (size == 3 && !ft_memcmp(buff, "\33\133\102", 3))
		return (2);
	if (size == 3 && !ft_memcmp(buff, "\33\133\103", 3))
		return (3);
	if (size == 3 && !ft_memcmp(buff, "\33\133\104", 3))
		return (4);
	if (buff[0] == 10)
		return (5);
	if (size == 1 && buff[0] == 3)
		return (6);
	return (-1);
}

/*
** Write the string to detect escape sequence
** DEV ONLY
*/

void			display_escape_code(char *buff, int size)
{
	int		i;

	printf("\n Escape code: \"");
	i = 0;
	while (i < size)
	{
		printf("\\%o", buff[i]);
		i++;
	}
	printf("\"\n");
}
