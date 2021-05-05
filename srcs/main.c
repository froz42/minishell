/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 10:44:38 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/05 15:14:11 by tmatis           ###   ########.fr       */
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

t_bool		check_exit(t_list *commands_list)
{
	t_command	command;

	command = *(t_command *)((t_list *)commands_list->content)->content;
	if (ft_lstsize(commands_list) == 1)
	{
		if (ft_strcmp(command.cmd, "exit") == 0)
		{
			if (ft_lstsize(command.args) > 1)
			{
				ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
				return (0);
			}
			if (ft_lstsize(command.args) == 1)
				return (ft_atoi(command.args->content) + 2);
			else
				return (0 + 2);
		}
	}
	return (0);
}

int		parse_exec(t_list *commands_list, t_list **env_var)
{
	t_list	*backup;
	int		ret;

	backup = commands_list;
	while (commands_list)
	{
		ret = check_exit(commands_list);
		if (!ret)
			ret = exec_pipes(commands_list->content, env_var);
		if (ret)
		{
			ft_lstclear(&backup, free_command_list);
			return (ret);
		}
		commands_list = commands_list->next;
	}
	ft_lstclear(&backup, free_command_list);
	return (0);
}

int		minishell(t_list **env_var, t_list *history)
{
	char	*line;
	int		ret;

	edit_var(env_var, "?", "0");
	ret = 0;
	while (1)
	{
		ft_putstr("Minishell $>");
		if (!get_input_line(&line, true, &history))
			break ;
		ret = parse_exec(parse_line(line, *env_var), env_var);
		if (ret)
			break ;
		free(line);
	}
	ft_lstclear(&history, free);
	free(line);
	return (ret - 2);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*env_var;
	int		ret;

	mute_unused(argc, argv);
	env_var = build_var(envp);
	write_header();
	ret = minishell(&env_var, NULL);
	ft_lstclear(&env_var, free_var);
	return (ret);
}
