/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 10:44:38 by tmatis            #+#    #+#             */
/*   Updated: 2021/03/31 14:27:14 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

/*
** Write a beautifull header O_O
** TODO: COLOR
*/

static	void	write_header(void)
{
	ft_putnl("        _       _     _          _ _");
	ft_putnl("  /\\/\\ (_)_ __ (_)___| |__   ___| | |");
	ft_putnl(" /    \\| | '_ \\| / __| '_ \\ / _ \\ | |");
	ft_putnl("/ /\\/\\ \\ | | | | \\__ \\ | | |  __/ | |");
	ft_putnl("\\/    \\/_|_| |_|_|___/_| |_|\\___|_|_|");
	ft_putnl("");
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

/*
** Return an id from an escape sequence
** DEL -> 0
** ARROW_UP -> 1
** ARROW_DOWN -> 2
** ARROW_RIGHT -> 3
** ARROW_LEFT -> 4
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
	return (-1);
}

/*
** Set terminal in raw mode (char by char)
*/

static	void	raw_mode(void)
{
	struct	termios	termios;

	tcgetattr(STDIN_FILENO, &termios);
	termios.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios);
}

int				main(void)
{
	int			ret;
	char		buff[10];
	t_buffer	buffer;
	t_list		*history;
	int			char_typed;

	history = NULL;
	if (isatty(STDOUT_FILENO))
	{
		write_header();
		raw_mode();
	}
	while (1)
	{
		buff[0] = 0;
		buffer = init_buffer();
		char_typed = 0;
		ft_putstr("Minishell $>");
		while (buff[0] != 10)
		{
			ret = read(STDIN_FILENO, buff, sizeof(buff));
			if (buff[0] != 10 && ft_iscntrl(buff[0]))
			{
				if (get_escape_id(buff, ret) == 0 && char_typed)
				{
					ft_putstr("\b \b");
					char_typed--;
				}
			}
			else
			{
				buffer_add(buff[0], &buffer);
				write(1, buff, ret);
				char_typed += ret;
			}
		}
		printf("command: |%s|\n", buffer.buff);
		if (buffer.buff)
			push_history(buffer.buff, &history);
		if (!ft_strcmp(buffer.buff, "exit"))
			break ;
	}
	ft_lstclear(&history, &free);
}
