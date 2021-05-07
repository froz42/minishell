/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 10:44:38 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/07 16:13:47 by tmatis           ###   ########.fr       */
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

void	return_value_buildin(int func_return, t_list **env_var, int *return_value)
{
	char	*status_str;

	status_str = ft_itoa(func_return);
	edit_var(env_var, "?", status_str);
	ft_safe_free(status_str);
	*return_value = 1;
}

int		 handle_buildin(t_list *commands_list, t_list **env_var)
{
	t_command	command;
	char		**argv;
	int			argc;
	int			return_value;

	return_value = 0;
	command = *(t_command *)((t_list *)commands_list->content)->content;
	if (ft_lstsize(commands_list) == 1)
	{
		argv = build_argv(command.name, command.args);
		argc = build_argc(argv);
		if (ft_strcmp(command.name, "cd") == 0)
			return_value_buildin(ft_cd(argc, argv, env_var), env_var, &return_value);
		else if (ft_strcmp(command.name, "echo") == 0)
			return_value_buildin(ft_echo(argc, argv), env_var, &return_value);
		else if (ft_strcmp(command.name, "env") == 0)
			return_value_buildin(ft_env(*env_var), env_var, &return_value);
		else if (ft_strcmp(command.name, "unset") == 0)
			return_value_buildin(ft_unset(argc, argv, env_var), env_var, &return_value);
		else if (ft_strcmp(command.name, "pwd") == 0)
			return_value_buildin(ft_pwd(), env_var, &return_value);
		else if (ft_strcmp(command.name, "exit") == 0)
			return_value = ft_exit(argc, argv, env_var, true) + 2;
		free_table(&argv);
	}
	return (return_value);
}

int		parse_exec(t_list *commands_list, t_list **env_var)
{
	t_list	*backup;
	int		ret;

	backup = commands_list;
	while (commands_list)
	{
		ret = handle_buildin(commands_list, env_var);
		if (!ret)
			ret = exec_pipes(commands_list->content, env_var);
		if (ret > 1)
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
		print_prompt();
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
