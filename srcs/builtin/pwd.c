/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 14:25:27 by tmatis            #+#    #+#             */
/*   Updated: 2021/06/01 11:04:17 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_pwd(void)
{
	char	actual_dir[BUFFER_SIZE];

	if (!getcwd(actual_dir, sizeof(actual_dir)))
	{
		file_error("cannot get PWD", strerror(errno));
		return (1);
	}
	ft_putstr_fd(actual_dir, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
