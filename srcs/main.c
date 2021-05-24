/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 10:44:38 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/24 13:47:00 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static t_bool	build_var(char **envp, t_list **var_list)
{
	t_var	*var;
	t_list	*elem;

	*var_list = NULL;
	while (*envp)
	{
		var = create_var(*envp);
		if (var)
			elem = ft_lstnew(var);
		if (!var || !elem)
		{
			ft_lstclear(var_list, free_var);
			if (var)
				load_var_error(ENV_VAR_ERROR, var, NULL);
			return (false);
		}
		ft_lstadd_back(var_list, elem);
		envp++;
	}
	if (!edit_var(var_list, "?", "0"))
	{
		ft_lstclear(var_list, free_var);
		return (false);
	}
	return (true);
}

static t_bool	close_std_fd(void)
{
	if (close(STDIN_FILENO) == -1)
	{
		ft_log_error(strerror(errno));
		return (false);
	}
	if (close(STDOUT_FILENO) == -1)
	{
		ft_log_error(strerror(errno));
		return (false);
	}
	if (close(STDERR_FILENO) == -1)
	{
		ft_log_error(strerror(errno));
		return (false);
	}
	return (true);
}

static t_bool	edit_shlvl_var(t_list **var_list)
{
	char	*shlvl;

	shlvl = search_var(*var_list, "SHLVL");
	if (shlvl)
	{
		shlvl = ft_itoa(ft_atoi(shlvl) + 1);
		if (!shlvl || !edit_var(var_list, "SHLVL", shlvl))
		{
			if (!shlvl)
				load_var_error(ENV_VAR_ERROR, NULL, NULL);
			ft_safe_free(shlvl);
			ft_lstclear(var_list, free_var);
			return (false);
		}
		free(shlvl);
	}
	else if (!edit_var(var_list, "SHLVL", "1"))
	{
		ft_lstclear(var_list, free_var);
		return (false);
	}
	return (true);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*env_var;
	int		ret;

	(void)argc;
	(void)argv;
	if (!build_var(envp, &env_var) || !edit_shlvl_var(&env_var))
	{
		close_std_fd();
		return (127);
	}
	if (isatty(STDIN_FILENO))
		write_header();
	ret = minishell(&env_var, NULL);
	ft_lstclear(&env_var, free_var);
	if (!close_std_fd())
		return (127);
	return (ret);
}
