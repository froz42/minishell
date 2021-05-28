/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 13:24:16 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/28 13:24:55 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_manager.h"

static char	*get_last_dir(void)
{
	char	actual_dir[4098];
	char	**split;
	int		i;
	char	*last_dir;

	getcwd(actual_dir, sizeof(actual_dir));
	split = ft_split(actual_dir, '/');
	if (!split)
		return (NULL);
	i = 0;
	while (split[i])
		i++;
	if (i > 0)
		last_dir = ft_strdup(split[i - 1]);
	else
		return (ft_strdup("/"));
	free_table(&split);
	return (last_dir);
}

/*
** Print the prompt
*/

void	print_prompt(char *status)
{
	char	*user;
	char	*last_dir;

	user = getenv("USER");
	ft_putstr("\x1B[32m");
	if (user)
		ft_putstr(user);
	ft_putstr("\x1B[37m@");
	ft_putstr("\x1B[34mminishell");
	last_dir = get_last_dir();
	if (last_dir)
	{
		ft_putstr("\x1B[37m (\x1B[33m");
		ft_putstr(last_dir);
		free(last_dir);
		ft_putstr("\x1B[37m)");
	}
	ft_putstr(" (");
	if (ft_atoi(status) > 0)
		ft_putstr("\x1B[31m");
	else
		ft_putstr("\x1B[32m");
	ft_putstr(status);
	ft_putstr("\x1B[0m)");
	ft_putstr("$ ");
}
