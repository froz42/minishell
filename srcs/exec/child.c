/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 19:28:54 by tmatis            #+#    #+#             */
/*   Updated: 2021/06/01 00:02:11 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	close_unused_fds(int index, int size, t_tube *tube_list)
{
	int	i;

	i = 0;
	while (i < (index - 1))
	{
		close(tube_list[i][0]);
		close(tube_list[i][1]);
		i++;
	}
	if (index != 0)
		close(tube_list[i++][1]);
	if (i < size)
		close(tube_list[i++][0]);
	while (i < size)
	{
		close(tube_list[i][0]);
		close(tube_list[i][1]);
		i++;
	}
}

static int	close_open_fd_child(t_tube *tube_list,
											int forks_running, int fork_n)
{
	close_unused_fds(forks_running, (fork_n - 1), tube_list);
	if (forks_running != 0)
	{
		if (dup2(tube_list[forks_running - 1][0], STDIN_FILENO) < 0)
		{
			close(tube_list[forks_running - 1][0]);
			if (forks_running < (fork_n - 1))
				close(tube_list[forks_running][1]);
			return (-1);
		}
		close(tube_list[forks_running - 1][0]);
	}
	if (forks_running < (fork_n - 1))
	{
		if (dup2(tube_list[forks_running][1], STDOUT_FILENO) < 0)
		{
			close(tube_list[forks_running][1]);
			return (-1);
		}
		close(tube_list[forks_running][1]);
	}
	return (0);
}

int	child_process(t_child_data child_data)
{
	int	return_value;

	if (close_open_fd_child(child_data.tube_list, child_data.forks_running,
			child_data.fork_n) < 0)
		return (handle_dup2_error(child_data.tube_list));
	return_value = execution_rules(child_data.command, child_data.env_var);
	free(child_data.tube_list);
	return (return_value);
}
