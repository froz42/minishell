/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 14:25:27 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/16 11:26:28 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"

int		ft_pwd(void)
{
	char	actual_dir[BUFFER_SIZE];

	getcwd(actual_dir, sizeof(actual_dir));
	ft_putstr_fd(actual_dir, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}