/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 22:29:02 by tmatis            #+#    #+#             */
/*   Updated: 2021/06/01 11:02:51 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static t_bool	is_valid_option(char *str)
{
	if (*str != '-')
		return (false);
	str++;
	while (*str == 'n')
		str++;
	if (*str == '\0')
		return (true);
	else
		return (false);
}

static int	number_of_options(int argc, char **argv)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if (!is_valid_option(argv[i]))
			return (i);
		i++;
	}
	return (i);
}

int	ft_echo(int argc, char **argv)
{
	int		i;
	t_bool	n_option;

	n_option = false;
	i = number_of_options(argc, argv);
	if (i > 1)
		n_option = true;
	while (i < argc)
	{
		ft_putstr(argv[i]);
		if ((i + 1) < argc)
			ft_putstr(" ");
		i++;
	}
	if (!n_option)
		ft_putstr("\n");
	return (0);
}
