/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 22:29:02 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/06 22:40:38 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"

int		ft_echo(int argc, char **argv)
{
	int		i;
	t_bool	n_option;

	n_option = false;
	if (argc >= 2)
	{
		if (ft_strcmp(argv[1], "-n") == 0)
		{
			argv++;
			argc--;
			n_option = true;
		}
		i = 1;
		while (i < argc)
		{
			ft_putstr(argv[i]);
			if ((i + 1) < argc)
				ft_putstr(" ");
			i++;
		}
		if (!n_option)
			ft_putstr("\n");
	}
	return (0);
}