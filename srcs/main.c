/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 10:44:38 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/19 15:00:52 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

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

void	mute_unused(int argc, char **argv)
{
	(void)argc;
	(void)argv;
}

/*
** Cette fonction va decider a l'aide de istty si on utilse gnl ou get_input
*/

int	read_next_line(char **line, t_list **history, char *status)
{
	int		left_to_read;

	if (isatty(STDIN_FILENO))
		return (get_input_line(line, true, history, status));
	left_to_read = get_next_line(STDIN_FILENO, line);
	if (left_to_read < 0)
		file_error("STDIN_FILENO", strerror(errno));
	else if (left_to_read == 0 && (*line)[0] != '\0')
		left_to_read = 1;
	return (left_to_read);
}

int	minishell(t_list **env_var, t_list *history)
{
	char	*line;
	int		ret;
	int		left_to_read;

	if (edit_var(env_var, "?", "0") == false)
		return (127);
	ret = 0;
	while (1)
	{
		left_to_read = read_next_line(&line, &history, search_var(*env_var, "?"));
		if (left_to_read < 0)
			break ;
		if (!left_to_read)
		{
			ret = ft_exit(1, NULL, env_var, false);
			break ;
		}
		ret = exec_line(line, env_var);
		if (ret)
			break ;
		free(line);
	}
	ft_lstclear(&history, free);
	if (left_to_read >= 0)
		ft_safe_free(line);
	return (ret - 2);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*env_var;
	int		ret;

	mute_unused(argc, argv);
	env_var = build_var(envp);
	if (env_var)
	{
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
