/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 14:12:05 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/07 14:07:37 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <sys/wait.h>

void	close_unused_fds(int index, int	size, t_tube *tube_list)
{
	int		i;

	i = 0;
	while (i < (index - 1))
	{
		close(tube_list[i][0]);
		close(tube_list[i][1]);
		i++;
	}
	if (index != 0)
	{
		close(tube_list[i++][1]);
	}
	if (i < size)
	{
		close(tube_list[i++][0]);
	}
	while (i < size)
	{
		close(tube_list[i][0]);
		close(tube_list[i][1]);
		i++;
	}
}

void	close_all_pipes(t_tube *tube_list, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		close(tube_list[i][0]);
		close(tube_list[i][1]);
		i++;
	}
}

int	build_in(char **argv, t_list **env_var)
{
	int		argc;

	argc = build_argc(argv);
	if (ft_strcmp(argv[0], "cd") == 0)
		return (ft_cd(argc, argv, env_var));
	else if (ft_strcmp(argv[0], "exit") == 0)
		return (ft_exit(argc, argv, env_var));
	else if (ft_strcmp(argv[0], "echo") == 0)
		return (ft_echo(argc, argv));
	else if (ft_strcmp(argv[0], "env") == 0)
		return (ft_env(*env_var));
	else if (ft_strcmp(argv[0], "unset") == 0)
		return (ft_unset(argc, argv, env_var));
	else
		return (0);
}

void	execution_error_write(char *cmd, int error)
{
	ft_putstr_fd("Minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(error), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

int		exec_pipes(t_list *pipes_list, t_list **env_vars)
{
	char		**envp;
	char		**argv;
	t_tube		*tube_list;
	pid_t		last_pid;
	pid_t		pid;
	int			fork_n;
	int			i;
	t_command	command;
	int			status;
	int			return_value;

	envp = build_env(*env_vars);
	fork_n = ft_lstsize(pipes_list);
	tube_list = calloc(fork_n - 1, sizeof(t_tube));
	i = 0;
	while (i < (fork_n - 1))
		pipe(tube_list[i++]);
	i = 0;
	while (pipes_list)
	{
		command = *(t_command *)pipes_list->content;
		argv = build_argv(command.name, command.args);
		last_pid = fork();
		if (last_pid == 0)
		{
			close_unused_fds(i, (fork_n - 1), tube_list);
			if (i != 0)
				dup2(tube_list[i - 1][0], STDIN_FILENO);
			if (i < (fork_n -1))
				dup2(tube_list[i][1], STDOUT_FILENO);
			return_value = build_in(argv, env_vars);
			if (!return_value)
			{
				execve(command.cmd, argv, envp);
				return_value = errno;
				execution_error_write(argv[0], return_value);
			}
			if (i < (fork_n -1))
				close(tube_list[i][1]);
			if (i != 0)
				close(tube_list[i - 1][0]);
			free_table(&argv);
			free_table(&envp);
			free(tube_list);
			return (return_value + 2);
		}
		free_table(&argv);
		i++;
		pipes_list = pipes_list->next;
	}
	free_table(&envp);
	close_all_pipes(tube_list, fork_n - 1);
	while (fork_n)
	{
		pid = wait(&status);
		char	*status_str;
		if (pid == last_pid)
		{
			status_str = ft_itoa(WEXITSTATUS(status));
			edit_var(env_vars, "?", status_str);
			free(status_str);
		}
		fork_n--;
	}
	free(tube_list);
	return (0);
}
