/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_rules.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 19:24:22 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/22 19:30:44 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <sys/stat.h>

static t_bool is_directory(const char *path)
{
	struct stat statbuf;

	if (stat(path, &statbuf) != 0)
		return (true);
	return (S_ISDIR(statbuf.st_mode));
}

int build_in(char **argv, t_list **env_var)
{
	int argc;

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

int execution_rules(t_command command, t_list **env_vars)
{
	char **argv;
	char **envp;
	int return_value;
	int backup[2];

	return_value = 0;
	if (redirect_fd(command, backup))
		return_value = 1 + 2;
	if (command.name)
	{
		argv = build_argv(command.name, command.args);
		if (!argv)
		{
			execution_error_write("Alloc error", strerror(errno));
			return (errno + 2);
		}
		envp = build_env(*env_vars);
		if (!envp)
		{
			execution_error_write("Alloc error", strerror(errno));
			free_table(&argv);
			return (errno + 2);
		}
		if (!return_value)
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
		free_table(&argv);
		free_table(&envp);
	}
	restore_in_out(backup);
	return (return_value);
}