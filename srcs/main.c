/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 10:44:38 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/08 14:58:24 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>
#include <fcntl.h>
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

int	return_value_buildin(int func_return, t_list **env_var)
{
	char	*status_str;

	status_str = ft_itoa(func_return);
	edit_var(env_var, "?", status_str);
	ft_safe_free(status_str);
	return (1);
}

int	get_open_flags(int type)
{
	if (type == 1)
		return (O_CREAT | O_WRONLY);
	else if (type == 2)
		return (O_RDONLY);
	else
		return (O_CREAT | O_WRONLY | O_APPEND);
}

void	file_error(char *file, char *error)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
}

int	redirect_fd(t_command command, int backup[2])
{
	t_list	*redir_list;
	t_redir	redir;
	int		open_file;

	backup[0] = dup(STDIN_FILENO);
	backup[1] = dup(STDOUT_FILENO);
	redir_list = command.redirs;
	while (redir_list)
	{
		redir = *(t_redir *)redir_list->content;
		open_file = open(redir.file, get_open_flags(redir.type), 0664);
		if (open_file < 0)
		{
			file_error(redir.file, strerror(errno));
			dup2(backup[0], STDIN_FILENO);
			dup2(backup[1], STDOUT_FILENO);
			return (1);
		}
		else
		{
			if (redir.type == 1 || redir.type == 4)
				dup2(open_file, STDOUT_FILENO);// STD_OUT
			else
				dup2(open_file, STDIN_FILENO);//STD_IN
		}
		redir_list = redir_list->next;
	}
	return (0);
}

int		 handle_buildin(t_list *commands_list, t_list **env_var)
{
	t_command	command;
	char		**argv;
	int			argc;
	int			ret;
	int			fd_backup[2];

	ret = 0;
	if (ft_lstsize(commands_list) == 1)
	{
		command = *(t_command *)commands_list->content;
		if (redirect_fd(command, fd_backup))
			ret = return_value_buildin(1, env_var);
		else
		{
			argv = build_argv(command.name, command.args);
			argc = build_argc(argv);
			if (ft_strcmp(command.name, "cd") == 0)
				ret = return_value_buildin(ft_cd(argc, argv, env_var), env_var);
			else if (ft_strcmp(command.name, "echo") == 0)
				ret = return_value_buildin(ft_echo(argc, argv), env_var);
			else if (ft_strcmp(command.name, "env") == 0)
				ret = return_value_buildin(ft_env(*env_var), env_var);
			else if (ft_strcmp(command.name, "unset") == 0)
				ret = return_value_buildin(ft_unset(argc, argv, env_var), env_var);
			else if (ft_strcmp(command.name, "pwd") == 0)
				ret = return_value_buildin(ft_pwd(), env_var);
			else if (ft_strcmp(command.name, "export") == 0)
				ret = return_value_buildin(ft_export(argc, argv, env_var), env_var);
			else if (ft_strcmp(command.name, "exit") == 0)
				ret = ft_exit(argc, argv, env_var, true) + 2;
			free_table(&argv);
			if (ft_lstsize(command.redirs) > 0)
			{
				dup2(fd_backup[0], STDIN_FILENO);
				dup2(fd_backup[1], STDOUT_FILENO);
			}
		}
	}
	return (ret);
}

int		parse_exec(t_list *commands_list, t_list **env_var)
{
	t_list	*backup;
	int		ret;

	backup = commands_list;
	while (commands_list)
	{
		ret = handle_buildin(commands_list->content, env_var);
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
		{
			ret = ft_exit(1, NULL, env_var, true) + 2;
			break ;
		}
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
