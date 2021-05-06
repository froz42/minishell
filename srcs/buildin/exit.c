/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 11:39:53 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/06 12:12:28 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_exit(int argc, char **argv)
{
	if (argc > 2)
	{
		ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
		return (1);
	}
	else if (argc == 2)
		return (ft_atoi(argv[1]));
	else
		return (0);
}