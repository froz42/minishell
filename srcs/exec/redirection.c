/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 14:16:18 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/22 13:25:18 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <fcntl.h>

int	backup_int_out(int backup[2])
{
	backup[0] = dup(STDIN_FILENO);
	if (backup[0] < 0)
	{
		ft_putstr_fd("Minishell: STDIN save fail\n", 2);
		return (1);
	}
	backup[1] = dup(STDOUT_FILENO);
	if (backup[0] < 0)
	{
		ft_putstr_fd("Minishell: STDOUT save fail\n", 2);
		close(backup[0]);
		return (1);
	}
	return (0);
}

int	open_file_redir(t_redir redir)
{
	int open_file;

	if (!redir.file)
	{
		ft_putstr_fd("Minishell: ambiguous redirect\n", 2);
		return (-1);
	}
	open_file = open(redir.file, get_open_flags(redir.type), 0664);
	if (open_file < 0)
	{
		file_error(redir.file, strerror(errno));
		return (-1);
	}
	return (open_file);
}

int	dup_in_or_out(t_redir redir)
{
	int	dup_return;
	int	open_file;

	open_file = open_file_redir(redir);
	if (open_file < 0)
		return (-1);
	if (redir.type == 1 || redir.type == 4)
		dup_return = dup2(open_file, STDOUT_FILENO);
	else
		dup_return = dup2(open_file, STDIN_FILENO);
	close(open_file);
	return (dup_return);
}

int redirect_fd(t_command command, int backup[2])
{
	t_list *redir_list;
	t_redir redir;
	int	dup_return;

	if (backup_int_out(backup))
		return (1);
	redir_list = command.redirs;
	while (redir_list)
	{
		redir = *(t_redir *)redir_list->content;
		if (!redir.file)
		{
			ft_putstr_fd("Minishell: ambiguous redirect\n", 2);
			return (1);
		}
		dup_return = dup_in_or_out(redir);
		if (dup_return < 0)
			return (redir_dup_fail(redir.file, backup));
		redir_list = redir_list->next;
	}
	return (0);
}