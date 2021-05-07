/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 15:40:14 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/07 15:44:39 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"

static int	print_var_sorted(t_list *env_var)
{
	return (0);
}

int		ft_export(int argc, char **argv, t_list **env_var)
{
	if (argc == 2)
		return (print_var_sorted(*env_var));
	return (0);
}