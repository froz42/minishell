/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 16:33:02 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/23 15:20:24 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*load_var_error(char *message, t_var *var_to_free, void *ret)
{
	if (var_to_free)
		free_var(var_to_free);
	ft_putstr_fd("Minishell: ", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	if (errno != 0)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
	return (ret);
}

void	write_error(int error_number)
{
	char	*error_table[10];

	error_table[0] = "unexpected EOL while looking for matching `\"'";
	error_table[1] = "unexpected EOL while looking for matching `''";
	error_table[2] = "syntax error: unexpected end of line";
	error_table[3] = "syntax error near unexpected token `>'";
	error_table[4] = "syntax error near unexpected token `<'";
	error_table[5] = "syntax error near unexpected token `|'";
	error_table[6] = "syntax error near unexpected token `>>'";
	error_table[7] = "syntax error near unexpected token `;'";
	error_table[8] = "syntax error near unexpected token `newline'";
	if (error_number < LOG_ERROR)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(error_table[error_number], 2);
		ft_putstr_fd("\n", 2);
	}
	else
		ft_log_error(strerror(errno));
}
