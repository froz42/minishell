/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 22:37:57 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/12 12:58:05 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	return_value_buildin(int func_return, t_list **env_var)
{
	char	*status_str;

	status_str = ft_itoa(func_return);
	edit_var(env_var, "?", status_str);
	ft_safe_free(status_str);
	return (1);
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
		argv = build_argv(command.name, command.args);
		argc = build_argc(argv);
		if (redirect_fd(command, fd_backup))
			ret = return_value_buildin(1, env_var);
		else if (ft_strcmp(command.name, "cd") == 0)
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
		dup2(fd_backup[0], STDIN_FILENO);
		dup2(fd_backup[1], STDOUT_FILENO);
		close(fd_backup[0]);
		close(fd_backup[1]);
	}
	return (ret);
}

int		exec(t_list *pipes_list, t_list **env_var)
{
	int		ret;

	ret = handle_buildin(pipes_list, env_var);
	if (ret == 0)
		ret = exec_pipes(pipes_list, env_var);
	if (ret > 1)
		return (ret);
	return (0);
}