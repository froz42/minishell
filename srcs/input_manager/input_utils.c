/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 21:19:47 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/16 17:26:48 by jmazoyer         ###   ########.fr       */
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
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios);	// test avec TCSANOW ?
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

/*
** Return an id from an escape sequence
** DEL (DEL = ASCII 127) -> DEL_ID -> 0
** BS (BS = ASCII 8) -> DEL_ID -> 0
** UP_KEY ("\33\133\101") -> UP_KEY_ID -> 1
** DOWN_KEY ("\33\133\102") -> DOWN_KEY_ID -> 2
** RIGHT_KEY ("\33\133\103") -> RIGHT_KEY_ID -> 3
** LEFT_KEY ("\33\133\104") -> LEFT_KEY_ID -> 4
** RETURN (LF = ASCII 10) -> LF_ID -> 5
** CTRL-C (ETX = ASCII 3) -> ETF_ID -> 6
** CTRL-D (EOT = ASCII 4) -> EOT_ID -> 7
** CTRL-L (FF = ASCII 12) -> CLR_SCREEN_ID -> 8
*/

int	get_escape_id(char *buff, int size)
{
	if (buff[0] == DEL || buff[0] == BS)
		return (DEL_ID);
	if (size == 3 && !ft_memcmp(buff, UP_KEY, 3))
		return (UP_KEY_ID);
	if (size == 3 && !ft_memcmp(buff, DOWN_KEY, 3))
		return (DOWN_KEY_ID);
	if (size == 3 && !ft_memcmp(buff, RIGHT_KEY, 3))
		return (RIGHT_KEY_ID);
	if (size == 3 && !ft_memcmp(buff, LEFT_KEY, 3))
		return (LEFT_KEY_ID);
	if (buff[0] == LF)
		return (LF_ID);
	if (size == 1 && buff[0] == ETX)
		return (ETX_ID);
	if (size == 1 && buff[0] == EOT)
		return (EOT_ID);
	if (size == 1 && buff[0] == FF)
		return (CLR_SCREEN_ID);
	return (-1);
}

/*
** Write the string to detect escape sequence
** DEV ONLY
*/

void	display_escape_code(char *buff, int size)
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
