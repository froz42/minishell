/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_code.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 13:26:03 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/31 23:49:23 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_manager.h"

/*
** Return an id from an escape sequence
** DEL (DEL = ASCII 127) -> DEL_ID -> 0
** BS (BS = ASCII 8) -> DEL_ID -> 0
** UP_KEY ("\33\133\101") -> UP_KEY_ID -> 1
** DOWN_KEY ("\33\133\102") -> DOWN_KEY_ID -> 2
** RIGHT_KEY ("\33\133\103") -> RIGHT_KEY_ID -> 3
** LEFT_KEY ("\33\133\104") -> LEFT_KEY_ID -> 4
** RETURN (LF = ASCII 10) -> LF_ID -> 5
** CTRL-C (ETX = ASCII 3) -> ETX_ID -> 6
** CTRL-D (EOT = ASCII 4) -> EOT_ID -> 7
** CTRL-L (FF = ASCII 12) -> CLR_SCREEN_ID -> 8
** CTRL-RIGHT (WORD_RIGHT = "\33\133\61\73\65\103" -> WORD_RIGHT_ID -> 9
** CTRL-LEFT (WORD_LEFT = "\33\133\61\73\65\104" -> WORD_LEFT_ID -> 10
** CTRL-A (LINE_START = SOH = ASCII 1) -> LINE_START_ID -> 11
** HOME_KEY ("\33\133\110") -> LINE_START_ID -> 11
** CTRL-E (LINE_END = ENQ = ASCII 5) -> LINE_END_ID -> 12
** END_KEY ("\33\133\106") -> LINE_END_ID -> 12
** ALT-D (CUT_WORD_RIGHT = "\33\144") -> CUT_WORD_RIGHT_ID -> 13
** CTRL-W (CUT_WORD_LEFT = ETB = ASCII 23) -> CUT_WORD_LEFT_ID -> 14
** CTRL-U (CUT_LINE_START = NAK = ASCII 21) -> CUT_LINE_START_ID -> 15
** CTRL-E (CUT_LINE_END = VT = ASCII 11) -> CUT_LINE_END_ID -> 16
** CTRL-Y (PASTE = EM = ASCII 25) -> PASTE_ID -> 17
** SUPPR_KEY ("\33\133\63\176") -> SUPPR_ID -> 18
*/

static int	get_escape_id_part2(char *buff, int size)
{
	if (buff[0] == CUT_WORD_LEFT)
		return (CUT_WORD_LEFT_ID);
	if (size == 2 && !ft_memcmp(buff, CUT_WORD_RIGHT, 2))
		return (CUT_WORD_RIGHT_ID);
	if (size == 3 && !ft_memcmp(buff, UP_KEY, 3))
		return (UP_KEY_ID);
	if (size == 3 && !ft_memcmp(buff, DOWN_KEY, 3))
		return (DOWN_KEY_ID);
	if (size == 3 && !ft_memcmp(buff, RIGHT_KEY, 3))
		return (RIGHT_KEY_ID);
	if (size == 3 && !ft_memcmp(buff, LEFT_KEY, 3))
		return (LEFT_KEY_ID);
	if (size == 4 && !ft_memcmp(buff, SUPPR_KEY, 4))
		return (SUPPR_ID);
	if (size == 6 && !ft_memcmp(buff, WORD_RIGHT, 6))
		return (WORD_RIGHT_ID);
	if (size == 6 && !ft_memcmp(buff, WORD_LEFT, 6))
		return (WORD_LEFT_ID);
	return (-1);
}

int	get_escape_id(char *buff, int size)
{
	if (buff[0] == LF)
		return (LF_ID);
	if (buff[0] == DEL || buff[0] == BS)
		return (DEL_ID);
	if (buff[0] == ETX)
		return (ETX_ID);
	if (buff[0] == EOT)
		return (EOT_ID);
	if (buff[0] == FF)
		return (CLR_SCREEN_ID);
	if (buff[0] == LINE_START || (size == 3 && !ft_memcmp(buff, HOME_KEY, 3)))
		return (LINE_START_ID);
	if (buff[0] == LINE_END || (size == 3 && !ft_memcmp(buff, END_KEY, 3)))
		return (LINE_END_ID);
	if (buff[0] == PASTE)
		return (PASTE_ID);
	if (buff[0] == CUT_LINE_START)
		return (CUT_LINE_START_ID);
	if (buff[0] == CUT_LINE_END)
		return (CUT_LINE_END_ID);
	return (get_escape_id_part2(buff, size));
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
