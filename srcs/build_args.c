/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 11:45:21 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/08 14:23:52 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**build_env(t_list *env_var)
{
	char	**envp;
	int		i;
	char	*env_str;
	t_var	var;

	envp = ft_calloc(ft_lstsize(env_var), sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	while (env_var)
	{
		var = *(t_var *)env_var->content;
		if (!ft_strcmp(var.key, "?") || !var.data)
		{
			env_var = env_var->next;
			continue ;
		}
		env_str = ft_calloc(ft_strlen(var.key) + ft_strlen(var.data) + 2, sizeof(char));
		ft_strcat(env_str, var.key);
		ft_strcat(env_str, "=");
		ft_strcat(env_str, var.data);
		envp[i++] = env_str;
		env_var = env_var->next;
	}
	return (envp);
}

char	**build_argv(char *name, t_list *args)
{
	char	**argv;
	int		i;

	argv = ft_calloc(ft_lstsize(args) + 2, sizeof(char *));
	if (!argv)
		return (NULL);
	i = 0;
	if (name)
		argv[i++] = ft_strdup(name);
	while (args)
	{
		argv[i++] = ft_strdup(args->content);
		args = args->next;
	}
	return (argv);
}

int	build_argc(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}