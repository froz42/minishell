/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 16:33:02 by tmatis            #+#    #+#             */
/*   Updated: 2021/04/18 16:41:07 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_error(int error_number)
{
	char	*error_table[10];

	error_table[0] = "unexpected EOL while looking for matching `\"'";
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(error_table[error_number], 2);
	ft_putstr_fd("\n", 2);
}
