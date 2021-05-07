/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 13:43:28 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/07 14:10:10 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"

t_bool	is_inside_args(int argc, char **argv, char *key)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!ft_strcmp(argv[i], key))
			return (true);
		i++;
	}
	return (false);
}

int		ft_unset(int argc, char **argv, t_list **env_var)
{
	t_list *new_list;
	t_list *list;
	t_var	var;

	list = *env_var;
	new_list = NULL;
	while (list)
	{
		var = *(t_var *)list->content;
		if (!is_inside_args(argc, argv, var.key))
			ft_lstadd_back(&new_list, ft_lstnew(list->content));
		else
			free_var(list->content);
		list = list->next;
	}
	ft_lstclear(env_var, ft_nofree);
	*env_var = new_list;
	return (0);
}