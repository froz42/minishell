/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 14:12:05 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/31 23:18:44 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <sys/wait.h>
#include <signal.h>

static void	handle_status(int status, t_list **env_var)
{
	int	return_value;

	return_value = 0;
	if (WIFEXITED(status))
		return_value = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		return_value = WTERMSIG(status) + 128;
		if (return_value == 130)
			ft_putstr("\n");
		if (return_value == 131)
			ft_putstr("Quit (core dumped)\n");
		if (return_value == 139)
			ft_putstr("Segmentation fault (core dumped)\n");
	}
	set_status_env(env_var, return_value);
}

static void	harvest_child(int forks_running, pid_t last_pid, t_list **env_var)
{
	int		status;
	pid_t	pid;

	set_status_env(env_var, 0);
	while (forks_running)
	{
		pid = wait(&status);
		if (pid == last_pid)
			handle_status(status, env_var);
		forks_running--;
	}
}

static t_tube	*make_tubes(int fork_n, t_list **env_vars)
{
	t_tube	*tube_list;
	int		i;

	tube_list = ft_calloc(fork_n - 1, sizeof(t_tube));
	if (!tube_list)
	{
		execution_error_status("pipes alloc fail",
			strerror(errno), 127, env_vars);
		return (NULL);
	}
	i = 0;
	while (i < (fork_n - 1))
	{
		if (pipe(tube_list[i++]) < 0)
		{
			execution_error_status("pipe creation fail",
				strerror(errno), 127, env_vars);
			close_all_pipes(tube_list, i - 1);
			free(tube_list);
			return (NULL);
		}
	}
	return (tube_list);
}

static int	prepare_data(t_child_data *child_data, t_list *pipes_list,
		t_list **env_vars)
{
	child_data->fork_n = ft_lstsize(pipes_list);
	if (child_data->fork_n <= 0)
	{
		execution_error_status("prepare_data", "not enought pipes",
			127, env_vars);
		return (1);
	}
	child_data->env_var = env_vars;
	child_data->tube_list = make_tubes(child_data->fork_n, env_vars);
	if (!child_data->tube_list)
		return (1);
	child_data->forks_running = 0;
	return (0);
}

int	exec_pipes(t_list *pipes_list, t_list **env_vars)
{
	pid_t			last_pid;
	t_child_data	child_data;

	if (prepare_data(&child_data, pipes_list, env_vars))
		return (0);
	while (pipes_list)
	{
		child_data.command = (t_command *)pipes_list->content;
		last_pid = fork();
		if (last_pid < 0)
		{
			execution_error_status("fork", strerror(errno), 127, env_vars);
			break ;
		}
		if (last_pid == 0)
			return (child_process(child_data));
		child_data.forks_running++;
		pipes_list = pipes_list->next;
	}
	close_all_pipes(child_data.tube_list, child_data.fork_n - 1);
	free(child_data.tube_list);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	harvest_child(child_data.forks_running, last_pid, env_vars);
	return (0);
}
