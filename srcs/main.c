/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 10:44:38 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/23 15:21:56 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mute_unused(int argc, char **argv)
{
	(void)argc;
	(void)argv;
}

/*
** Write a beautifull header O_O
** TODO: COLOR
*/

static void	write_header(void)
{
	ft_putnl("        _       _     _          _ _");
	ft_putnl("  /\\/\\ (_)_ __ (_)___| |__   ___| | |");
	ft_putnl(" /    \\| | '_ \\| / __| '_ \\ / _ \\ | |");
	ft_putnl("/ /\\/\\ \\ | | | | \\__ \\ | | |  __/ | |");
	ft_putnl("\\/    \\/_|_| |_|_|___/_| |_|\\___|_|_|");
	ft_putnl("");
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
			return (load_var_error(ENV_VAR_ERROR, NULL, NULL));
		ft_lstadd_back(&var_list, elem);
		envp++;
	}
	return (var_list);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*env_var;
	int		ret;

	mute_unused(argc, argv);
	env_var = build_var(envp);
	if (env_var)
	{
		if (edit_var(&env_var, "?", "0") == false)
			return (127);
		if (isatty(STDIN_FILENO))
			write_header();
		ret = minishell(&env_var, NULL);
		ft_lstclear(&env_var, free_var);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		return (ret);
	}
	ft_lstclear(&env_var, free_var);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	return (127);
}
