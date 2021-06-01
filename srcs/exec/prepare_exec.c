/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 22:37:57 by tmatis            #+#    #+#             */
/*   Updated: 2021/06/01 11:03:55 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	return_value_builtin(int func_return, t_list **env_var)
{
	set_status_env(env_var, func_return);
	return (1);
}

static int	exec_builtin(char *command_name, int argc, char **argv,
															t_list **env_var)
{
	int	ret;

	ret = 0;
	if (ft_strcmp(command_name, "cd") == 0)
		ret = return_value_builtin(ft_cd(argc, argv, env_var), env_var);
	else if (ft_strcmp(command_name, "echo") == 0)
		ret = return_value_builtin(ft_echo(argc, argv), env_var);
	else if (ft_strcmp(command_name, "env") == 0)
		ret = return_value_builtin(ft_env(*env_var), env_var);
	else if (ft_strcmp(command_name, "unset") == 0)
		ret = return_value_builtin(ft_unset(argc, argv, env_var), env_var);
	else if (ft_strcmp(command_name, "pwd") == 0)
		ret = return_value_builtin(ft_pwd(), env_var);
	else if (ft_strcmp(command_name, "export") == 0)
		ret = return_value_builtin(ft_export(argc, argv, env_var), env_var);
	else if (ft_strcmp(command_name, "exit") == 0)
		ret = ft_exit(argc, argv, env_var, false);
	return (ret);
}

static int	alloc_error(t_list **env_var)
{
	ft_putstr_fd("Minishell: alloc failed\n", STDERR_FILENO);
	set_status_env(env_var, 127);
	return (1);
}

int	handle_builtin(t_list *commands_list, t_list **env_var)
{
	t_command	command;
	char		**argv;
	int			argc;
	int			ret;
	int			backup[2];

	ret = 0;
	if (ft_lstsize(commands_list) == 1)
	{
		command = *(t_command *)commands_list->content;
		if (!command.name)
			return (ret);
		argv = build_argv(command.name, command.args);
		if (!argv)
			return (alloc_error(env_var));
		argc = build_argc(argv);
		if (!redirect_fd(command, backup))
			ret = return_value_builtin(1, env_var);
		else
			ret = exec_builtin(command.name, argc, argv, env_var);
		free_table(&argv);
		restore_in_out(backup);
	}
	return (ret);
}

int	exec(t_list *pipes_list, t_list **env_var)
{
	int	ret;

	ret = handle_builtin(pipes_list, env_var);
	if (ret == 0)
		ret = exec_pipes(pipes_list, env_var);
	if (ret > 1)
		return (ret);
	return (0);
}
