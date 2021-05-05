/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:45:04 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/05 15:22:38 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Parse key=value
*/

t_var	*create_var(char *str)
{
	int		i;
	t_var	*var;

	var = ft_calloc(1, sizeof(t_var));
	if (!var)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	var->key = ft_substr(str, 0, i);
	str += i + 1;
	var->data = ft_strdup(str);
	return (var);
}

void	free_var(void *mem)
{
	t_var	*var;

	var = (t_var *)mem;
	ft_safe_free(var->key);
	ft_safe_free(var->data);
	ft_safe_free(var);
}

/*
** cherche une value selon la cle
*/

char	*search_var(t_list *var_list, char *key)
{
	t_var	*var;

	while (var_list)
	{
		var = (t_var *)var_list->content;
		if (!ft_strcmp(var->key, key))
			return (var->data);
		var_list = var_list->next;
	}
	return (NULL);
}

/*
** add a var or edit the one does exits
*/

void	edit_var(t_list **var_list, char *key, char *value)
{
	t_var	*var;
	t_list	*save;

	save = *var_list;
	while (save)
	{
		var = (t_var *)save->content;
		if (!ft_strcmp(var->key, key))
		{
			ft_safe_free(var->data);
			var->data = ft_strdup(value);
			return ;
		}
		save = save->next;
	}
	var = ft_calloc(1, sizeof(t_var));
	if (!var)
		return ;
	var->key = ft_strdup(key);
	var->data = ft_strdup(value);
	ft_lstadd_back(var_list, ft_lstnew(var));
}

/*
** envp -> list de var
*/

t_list	*build_var(char **envp)
{
	t_list	*var_list;

	var_list = NULL;
	while (*envp)
	{
		ft_lstadd_back(&var_list, ft_lstnew(create_var(*envp)));
		envp++;
	}
	return (var_list);
}
