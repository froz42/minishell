/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 13:43:28 by tmatis            #+#    #+#             */
/*   Updated: 2021/06/01 11:03:18 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	varcmp(t_var *var, t_var *ref)
{
	return (ft_strcmp(var->key, ref->key));
}

int	ft_unset(int argc, char **argv, t_list **env_var)
{
	int		i;
	t_var	var;

	i = 0;
	while (i < argc)
	{
		var.key = argv[i++];
		ft_lstremove_one_if(env_var, &var, varcmp, free_var);
	}
	return (0);
}
