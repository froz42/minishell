/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_rules.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 19:24:22 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/29 18:31:42 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <sys/stat.h>

static t_bool	is_directory(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (false);
	return (S_ISDIR(statbuf.st_mode));
}

static int	build_in(char **argv, t_list **env_var)
{
	int	argc;

	argc = build_argc(argv);
	if (ft_strcmp(argv[0], "cd") == 0)
		return (ft_cd(argc, argv, env_var) + 2);
	else if (ft_strcmp(argv[0], "exit") == 0)
		return (ft_exit(argc, argv, env_var, true) + 2);
	else if (ft_strcmp(argv[0], "echo") == 0)
		return (ft_echo(argc, argv) + 2);
	else if (ft_strcmp(argv[0], "env") == 0)
		return (ft_env(*env_var) + 2);
	else if (ft_strcmp(argv[0], "unset") == 0)
		return (ft_unset(argc, argv, env_var) + 2);
	else if (ft_strcmp(argv[0], "export") == 0)
		return (ft_export(argc, argv, env_var) + 2);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		return (ft_pwd() + 2);
	else
		return (0);
}

static int	rules(t_command command, char **argv,
				char **envp, t_list **env_vars)
{
	int	return_value;

	return_value = build_in(argv, env_vars);
	if (!return_value && !command.cmd)
	{
		execution_error_write(command.name, "command not found");
		return_value = 127 + 2;
	}
	if (!return_value)
	{
		if (is_directory(command.cmd))
		{
			execution_error_write(command.name, "Is a directory");
			return_value = 126 + 2;
		}
	}
	if (!return_value)
	{
		execve(command.cmd, argv, envp);
		execution_error_write(argv[0], strerror(errno));
		return_value = 127 + 2;
	}
	return (return_value);
}

static int	build_args_and_exec(t_command *command, t_list **env_vars)
{
	char	**argv;
	char	**envp;
	int		return_value;

	if (isatty(STDOUT_FILENO) && !ft_strcmp(command->name, "ls"))
		add_ls_color(command);
	argv = build_argv(command->name, command->args);
	if (!argv)
	{
		execution_error_write("argv: ", strerror(errno));
		return (errno + 2);
	}
	envp = build_env(*env_vars);
	if (!envp)
	{
		execution_error_write("envp: ", strerror(errno));
		free_table(&argv);
		return (errno + 2);
	}
	return_value = rules(*command, argv, envp, env_vars);
	free_table(&argv);
	free_table(&envp);
	return (return_value);
}

int	execution_rules(t_command *command, t_list **env_vars)
{
	int	return_value;
	int	backup[2];

	return_value = 2;
	if (!redirect_fd(*command, backup))
		return_value = 1 + 2;
	if (command->name && return_value == 2)
		return_value = build_args_and_exec(command, env_vars);
	restore_in_out(backup);
	return (return_value);
}
