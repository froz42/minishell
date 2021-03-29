/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 10:44:38 by tmatis            #+#    #+#             */
/*   Updated: 2021/03/29 22:09:00 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

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
static	int		get_escape_code(char *buff, int size)
{
	return (0)
}
*/
static	void	raw_mode(void)
{
	struct	termios	termios;

	tcgetattr(STDIN_FILENO, &termios);
	termios.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios);
}

int				main(int argc, char **argv)
{
	int			ret;
	char		buff[10];
	t_buffer	buffer;

	(void)argc;
	(void)argv;
	if (isatty(STDOUT_FILENO))
	{
		write_header();
		raw_mode();
	}
	while (1)
	{
		buff[0] = 0;
		buffer = init_buffer();
		ft_putstr("Minishell $>");
		while (buff[0] != 10)
		{
			ret = read(STDIN_FILENO, buff, sizeof(buff));
			if (buff[0] != 10 && ft_iscntrl(buff[0]))
			{
				if (buff[0] == 127)
					ft_putstr("\b \b");
			}
			else
			{
				buffer_add(buff[0], &buffer);
				write(1, buff, ret);
			}
		}
		printf("command: |%s|\n", buffer.buff);
		if (buffer.buff)
			free(buffer.buff);
	}
}
