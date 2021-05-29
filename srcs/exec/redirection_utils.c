/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 13:22:34 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/29 19:34:37 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <fcntl.h>

int	get_open_flags(int type)
{
	if (type == 1)
		return (O_CREAT | O_WRONLY | O_TRUNC);
	else if (type == 2)
		return (O_RDONLY);
	else
		return (O_CREAT | O_WRONLY | O_APPEND);
}

void	file_error(char *file, char *error)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
}

void	restore_in_out(int backup[2])
{
	if (backup[0] >= 0)
	{
		dup2(backup[0], STDIN_FILENO);
		if (close(backup[0]) < 0)
//			;
			file_error("Backup STDIN", strerror(errno));
	}
	if (backup[1] >= 0)
	{
		dup2(backup[1], STDOUT_FILENO);
		if (close(backup[1]) < 0)
//			;
			file_error("Backup STDOUT", strerror(errno));
	}
}

t_bool	redir_dup_fail(int backup[2])
{
	restore_in_out(backup);
	return (false);
}
