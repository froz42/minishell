/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 10:44:38 by tmatis            #+#    #+#             */
/*   Updated: 2021/04/06 15:25:44 by tmatis           ###   ########.fr       */
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

int				main(void)
{
	t_list	*history;
	char	*line;

	history = NULL;
	write_header();
	while (1)
	{
		ft_putstr("Minishell $>");
		line = get_input_line(&history);
		printf("Command: |%s|\n", line);
		if (!ft_strcmp(line, "exit"))
			break ;
		free(line);
	}
	ft_lstclear(&history, free);
	free(line);
}
