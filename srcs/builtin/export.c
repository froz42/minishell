/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 15:40:14 by tmatis            #+#    #+#             */
/*   Updated: 2021/06/01 11:03:05 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	append_var(t_list **env_var, char *work_str, char *key)
{
	char	*dest;
	char	*var;
	int		len_var;

	len_var = 0;
	var = search_var(*env_var, key);
	if (var)
		len_var = ft_strlen(var);
	dest = ft_calloc(len_var + ft_strlen(work_str) + 1, sizeof(char));
	if (!dest)
	{
		ft_log_error(strerror(errno));
		return ;
	}
	if (var)
		ft_strcat(dest, var);
	ft_strcat(dest, work_str);
	edit_var(env_var, key, dest);
	free(dest);
}

static void	add_var(char *key, char *work_str, t_list **env_var, int append)
{
	if (!*work_str && *(work_str - 1) != '=')
		edit_var(env_var, key, NULL);
	else
	{
		if (append)
			append_var(env_var, work_str, key);
		else
			edit_var(env_var, key, work_str);
	}
}

int	export_rules(char *str, t_list **env_var)
{
	char	*work_str;
	int		error;
	char	*key;
	int		append;

	error = 0;
	work_str = str;
	key = catch_key(&work_str, &error, &append);
	if (!key && !error)
	{
		execution_error_write("export", strerror(errno));
		return (1);
	}
	if (error)
	{
		ft_putstr_fd("Minishell: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("' not a valid indentifier\n", 2);
	}
	else
		add_var(key, work_str, env_var, append);
	ft_safe_free(key);
	return (error);
}

int	ft_export(int argc, char **argv, t_list **env_var)
{
	int		i;
	int		error;

	if (argc == 1)
		return (print_export(*env_var));
	i = 1;
	error = 0;
	while (i < argc)
	{
		if (export_rules(argv[i++], env_var))
			error = 1;
	}
	return (error);
}
