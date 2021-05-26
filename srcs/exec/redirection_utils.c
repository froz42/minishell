/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 13:22:34 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/25 13:10:31 by tmatis           ###   ########.fr       */
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
	dup2(backup[0], STDIN_FILENO);
	dup2(backup[1], STDOUT_FILENO);
	close(backup[0]);
	close(backup[1]);
}

int	redir_dup_fail(int backup[2])
{
	restore_in_out(backup);
	return (1);
}
