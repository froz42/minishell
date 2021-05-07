/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 14:25:27 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/07 14:28:01 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"

int		ft_pwd(void)
{
	char	actual_dir[BUFFER_SIZE];

	getcwd(actual_dir, sizeof(actual_dir));
	printf("%s\n", actual_dir);
	return (0);
}