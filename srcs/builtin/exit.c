/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 11:39:53 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/29 22:26:49 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_bool	is_str_numeric(char *str)
{
	if (*str == '+' || *str == '-')
		if (!*++str)
			return (false);
	while (*str)
	{
		if (!ft_isnum(*str))
			return (false);
		str++;
	}
	return (true);
}

static int	exit_not_numeric(char *argv_1, int offset)
{
	ft_putstr_fd("Minishell: exit: ", 2);
	ft_putstr_fd(argv_1, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	return (EXIT_ERROR + offset);
}

static int	exit_value(int argc, char **argv, t_list **env_var, int offset)
{
	int		ret;

	if (argc == 2)
		ret = ft_atoi(argv[1]);
	else
		ret = ft_atoi(search_var(*env_var, "?"));
	return ((unsigned char)(ret + offset));
}

int	ft_exit(int argc, char **argv, t_list **env_var, t_bool in_pipes)
{
	int		offset;

	if (in_pipes)
		offset = IN_PIPES;
	else
		offset = NOT_IN_PIPES;
	if (isatty(STDIN_FILENO))
		ft_putstr("exit\n");
	if (argc >= 2 && !is_str_numeric(argv[1]))
		return (exit_not_numeric(argv[1], offset));
	if (argc > 2)
	{
		ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
		edit_var(env_var, "?", "1");
		return (1);
	}
	else
		return (exit_value(argc, argv, env_var, offset));
}
