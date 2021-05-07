/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 15:40:14 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/07 16:40:37 by tmatis           ###   ########.fr       */
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
	printf("here\n");
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
	print_sorted(var_table);
	ft_safe_free(var_table);
	return (0);
}

int		ft_export(int argc, char **argv, t_list **env_var)
{
	(void)argv;
	if (argc == 1)
		return (print_export(*env_var));
	return (0);
}