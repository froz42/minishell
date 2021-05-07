/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 15:40:14 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/07 17:44:25 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"

static void	sort_vars(t_var **var_table)
{
	int		i;
	int		j;
	t_var	*temp;

	i = 0;
	while (var_table[i])
	{
		j = i + 1;
		while (var_table[j])
		{
			if (ft_strcmp(var_table[i]->key, var_table[j]->key) > 0)
			{
				temp = var_table[i];
				var_table[i] = var_table[j];
				var_table[j] = temp;
			}
			j++;
		}
		i++;
	}
}

static void	print_sorted(t_var	**var_table)
{
	while (*var_table)
	{
		ft_putstr("declare -x ");
		ft_putstr((*var_table)->key);
		if ((*var_table)->data)
		{
			ft_putstr("=\"");
			ft_putstr((*var_table)->data);
			ft_putstr("\"");
		}
		ft_putstr("\n");
		var_table++;
	}
}

static int	print_export(t_list *env_var)
{
	t_var	**var_table;
	t_var	*var;
	int		i;

	var_table = ft_calloc(ft_lstsize(env_var), sizeof(t_var *));
	i = 0;
	while (env_var)
	{
		var = (t_var *)env_var->content;
		if (!ft_strcmp(var->key, "?"))
		{
			env_var = env_var->next;
			continue ;
		}
		var_table[i++] = var;
		env_var = env_var->next;
	}
	sort_vars(var_table);
	print_sorted(var_table);
	ft_safe_free(var_table);
	return (0);
}

char	*catch_key(char **str, int *error)
{
	int		i;
	char	*dest;

	if (ft_isnum(**str))
	{
		*error = 1;
		return (NULL);
	}
	i = 0;
	while ((*str)[i] && ((*str)[i] == '_' || ft_isalnum((*str)[i])))
		i++;
	if ((*str)[i] != '=' && (*str)[i] != 0)
	{
		*error = 1;
		return (NULL);
	}
	dest = ft_substr(*str, 0, i);
	(*str) += i;
	return (dest);
}

void	add_var(char *key, char *work_str, t_list **env_var)
{
	if (!*work_str)
		edit_var(env_var, key, NULL);
	else
	{
		work_str++;
		edit_var(env_var, key, work_str);
	}
}

int		ft_export(int argc, char **argv, t_list **env_var)
{
	int		i;
	char	*work_str;
	int		error;
	char	*key;


	if (argc == 1)
		return (print_export(*env_var));
	i = 1;
	while (i < argc)
	{
		error = 0;
		work_str = argv[i];
		key = catch_key(&work_str, &error);
		if (error)
		{
			ft_putstr_fd("Minishell: export: `", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("' not a valid indentifier\n", 2);
		}
		else
			add_var(key, work_str, env_var);
		ft_safe_free(key);
		i++;
	}
	return (0);
}