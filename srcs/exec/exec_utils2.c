/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 19:31:28 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/28 16:23:00 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	sig_handler(int signal_no)
{
	(void)signal_no;
}

int	handle_dup2_error(t_tube *tube_list, int forks_running, int fork_n)
{
	execution_error_write("dup2 fail", strerror(errno));
	close_finish_tube(tube_list, forks_running, fork_n);
	return (errno + 2);
}

void	add_ls_color(t_command *command)
{
	char	*arg_string;
	t_list	*new;

	arg_string = ft_strdup(LS_COLOR);
	if (!arg_string)
		return ;
	new = ft_lstnew(arg_string);
	if (!new)
	{
		free(arg_string);
		return ;
	}
	ft_lstadd_back(&command->args, new);
}
