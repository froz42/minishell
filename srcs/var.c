/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:45:04 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/14 16:11:52 by jmazoyer         ###   ########.fr       */
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
		return (NULL);		// creer message d'erreur
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	var->key = ft_substr(str, 0, i);
	if (!var->key)
		return (NULL);		// creer message d'erreur
	str += i + 1;
	var->data = ft_strdup(str);
	if (!var->data)
		return (NULL);		// creer message d'erreur
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

static t_bool	add_var(t_list **var_list, char *key, char *value);

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
					return (false);	//creer message d'erreur
			}
			return (true);
		}
		current = current->next;
	}
	return (add_var(var_list, key, value));
}

static t_bool	add_var(t_list **var_list, char *key, char *value)
{
	t_var	*var;
	t_list	*elem;

	var = ft_calloc(1, sizeof(t_var));
	if (!var)
		return (false);		// creer message d'erreur
	var->key = ft_strdup(key);
	if (var->key && value)
		var->data = ft_strdup(value);
	if (!var->key || (value && !var->data))
	{
		free_var(var);
		return (false);		// creer message d'erreur
	}
	elem = ft_lstnew(var);
	if (!elem)
	{
		free_var(var);
		return (false);		// creer message d'erreur
	}
	ft_lstadd_back(var_list, elem);
	return (true);
}

/*
** envp -> list de var
*/

t_list	*build_var(char **envp)
{
	t_list	*var_list;
	t_var	*var;
	t_list	*elem;

	var_list = NULL;
	while (*envp)
	{
		var = create_var(*envp);
		if (!var)
			return (NULL);
		elem = ft_lstnew(var);
		if (!elem)
			return (NULL);		// creer message d'erreur
		ft_lstadd_back(&var_list, elem);
		envp++;
	}
	return (var_list);
}
