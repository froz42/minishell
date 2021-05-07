/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 12:42:16 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/07 13:40:22 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"

int		ft_env(t_list *env_var)
{
	int		i;
	char **envp;

	envp = build_env(env_var);
	if (!envp)
	{
		ft_putstr_fd("Minishell: env: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (errno);
	}
	i = 0;
	while (envp[i])
		printf("%s\n", envp[i++]);
	free_table(&envp);
	return (0);
}
