/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 13:13:37 by tmatis            #+#    #+#             */
/*   Updated: 2021/06/01 11:04:13 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	key_len(char *str, int *error)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == '_' || ft_isalnum(str[i])))
		i++;
	if (!i || (str[i] != '='
			&& ft_memcmp(str + i, "+=", 2) && str[i] != 0))
	{
		*error = 1;
		return (-1);
	}
	return (i);
}

char	*catch_key(char **str, int *error, int *append)
{
	int		i;
	char	*dest;

	if (ft_isnum(**str))
	{
		*error = 1;
		return (NULL);
	}
	i = key_len(*str, error);
	if (i < 0)
		return (NULL);
	if (!ft_memcmp((*str) + i, "+=", 2))
		*append = true;
	else
		*append = false;
	dest = ft_substr(*str, 0, i);
	if (!dest)
		return (NULL);
	if ((*str)[i])
		(*str) += 1;
	(*str) += i + *append;
	return (dest);
}

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
	ft_putstr("\033[0m");
}

int	print_export(t_list *env_var)
{
	t_var	**var_table;
	t_var	*var;
	int		i;

	var_table = ft_calloc(ft_lstsize(env_var), sizeof(t_var *));
	if (!var_table)
	{
		ft_log_error(strerror(errno));
		return (127);
	}
	i = 0;
	while (env_var)
	{
		var = (t_var *)env_var->content;
		env_var = env_var->next;
		if (!ft_strcmp(var->key, "?") || !ft_strcmp(var->key, "_"))
			continue ;
		var_table[i++] = var;
	}
	sort_vars(var_table);
	print_sorted(var_table);
	ft_safe_free(var_table);
	return (0);
}
