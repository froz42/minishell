/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 14:16:18 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/20 22:21:42 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <fcntl.h>

int get_open_flags(int type)
{
	if (type == 1)
		return (O_CREAT | O_WRONLY);
	else if (type == 2)
		return (O_RDONLY);
	else
		return (O_CREAT | O_WRONLY | O_APPEND);
}

void file_error(char *file, char *error)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
}

void restore_in_out(int backup[2])
{
	if (dup2(backup[0], STDIN_FILENO) < 0)
		execution_error_write("dup2", "Cannot restore STDIN");
	if (dup2(backup[1], STDOUT_FILENO) < 0)
		execution_error_write("dup2", "Cannot restore STDOUT");
	close(backup[0]);
	close(backup[1]);
}

static int redir_dup_fail(char *file, int backup[2], int open_file)
{
	file_error(file, "fail to dup2");
	close(open_file);
	restore_in_out(backup);
	return (1);
}

int redirect_fd(t_command command, int backup[2])
{
	t_list *redir_list;
	t_redir redir;
	int open_file;
	int	dup_return;

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
	redir_list = command.redirs;
	while (redir_list)
	{
		redir = *(t_redir *)redir_list->content;
		if (!redir.file)
		{
			ft_putstr_fd("Minishell: ambiguous redirect\n", 2);
			return (1);
		}
		open_file = open(redir.file, get_open_flags(redir.type), 0664);
		if (open_file < 0)
		{
			file_error(redir.file, strerror(errno));
			return (1);
		}
		else
		{
			if (redir.type == 1 || redir.type == 4)
				dup_return = dup2(open_file, STDOUT_FILENO);
			else
				dup_return = dup2(open_file, STDIN_FILENO);
			if (dup_return < 0)
				return (redir_dup_fail(redir.file, backup, open_file));
			close(open_file);
		}
		redir_list = redir_list->next;
	}
	return (0);
}