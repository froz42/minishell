/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 10:44:38 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/04 18:21:05 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

/*
** Write a beautifull header O_O
** TODO: COLOR
*/

static void	write_header(void)
{
	ft_putnl("        _       _     _          _ _");
	ft_putnl("  /\\/\\ (_)_ __ (_)___| |__   ___| | |");
	ft_putnl(" /    \\| | '_ \\| / __| '_ \\ / _ \\ | |");
	ft_putnl("/ /\\/\\ \\ | | | | \\__ \\ | | |  __/ | |");
	ft_putnl("\\/    \\/_|_| |_|_|___/_| |_|\\___|_|_|");
	ft_putnl("");
}

void	mute_unused(int argc, char **argv)
{
	(void)argc;
	(void)argv;
}

int		parse_exec(t_list *commands_list, t_list *env_var)
{
	t_list	*backup;

	backup = commands_list;
	while (commands_list)
	{
		if (exec_pipes(commands_list->content, env_var))
		{
			ft_lstclear(&backup, free_command_list);
			return (1);
		}
		commands_list = commands_list->next;
	}
	ft_lstclear(&backup, free_command_list);
	return (0);
}

void	minishell(t_list *env_var, t_list *history)
{
	char	*line;

	while (1)
	{
		ft_putstr("Minishell $>");
		if (!get_input_line(&line, true, &history))
			break ;
		if (parse_exec(parse_line(line, env_var), env_var))
			break ;
		if (!ft_strcmp(line, "exit"))
			break ;
		free(line);
	}
	ft_lstclear(&history, free);
	free(line);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*env_var;

	mute_unused(argc, argv);
	env_var = build_var(envp);
	write_header();
	minishell(env_var, NULL);
	ft_lstclear(&env_var, free_var);
}
