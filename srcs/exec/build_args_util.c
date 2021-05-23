/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_args_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 15:13:23 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/23 15:15:14 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	free_until(char **table, int max)
{
	int		i;

	i = 0;
	while (i < max)
		ft_safe_free(table[i++]);
	free(table);
}

void	*return_and_free(char **envp, int i)
{
	free_until(envp, i);
	return (NULL);
}
