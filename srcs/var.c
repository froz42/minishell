/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:45:04 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/30 13:51:08 by jmazoyer         ###   ########.fr       */
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

	errno = 0;
	var = ft_calloc(1, sizeof(t_var));
	if (!var)
		return (load_var_error(ENV_VAR_ERROR, NULL, NULL));
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	var->key = ft_substr(str, 0, i);
	if (!var->key)
		return (load_var_error(ENV_VAR_ERROR, var, NULL));
	str += i + 1;
	var->data = ft_strdup(str);
	if (!var->data)
		return (load_var_error(ENV_VAR_ERROR, var, NULL));
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
** add a var or edit an existing one
*/

static t_bool	add_var(t_list **var_list, char *key, char *value)
{
	t_var	*var;
	t_list	*elem;

	var = ft_calloc(1, sizeof(t_var));
	if (!var)
	{
		load_var_error(ENV_VAR_ERROR, NULL, NULL);
		return (false);
	}
	var->key = ft_strdup(key);
	if (var->key && value)
		var->data = ft_strdup(value);
	if (!var->key || (value && !var->data))
	{
		load_var_error(ENV_VAR_ERROR, var, NULL);
		return (false);
	}
	elem = ft_lstnew(var);
	if (!elem)
	{
		load_var_error(ENV_VAR_ERROR, var, NULL);
		return (false);
	}
	ft_lstadd_back(var_list, elem);
	return (true);
}

t_bool	edit_var(t_list **var_list, char *key, char *value)
{
	t_var	*var;
	t_list	*current;

	current = *var_list;
	while (current)
	{
		var = (t_var *)current->content;
		if (!ft_strcmp(var->key, key))
		{
			if (value)
			{
				ft_safe_free(var->data);
				var->data = ft_strdup(value);
				if (!var->data)
				{
					load_var_error(ENV_VAR_ERROR, NULL, NULL);
					return (false);
				}
			}
			return (true);
		}
		current = current->next;
	}
	return (add_var(var_list, key, value));
}
