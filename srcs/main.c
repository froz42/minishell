/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 10:44:38 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/15 15:28:21 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>
#include <fcntl.h>
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

int	get_open_flags(int type)
{
	if (type == 1)
		return (O_CREAT | O_WRONLY);
	else if (type == 2)
		return (O_RDONLY);
	else
		return (O_CREAT | O_WRONLY | O_APPEND);
}

void	file_error(char *file, char *error)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
}

int	redirect_fd(t_command command, int backup[2])
{
	t_list	*redir_list;
	t_redir	redir;
	int		open_file;

	backup[0] = dup(STDIN_FILENO);
	backup[1] = dup(STDOUT_FILENO);
	redir_list = command.redirs;
	while (redir_list)
	{
		redir = *(t_redir *)redir_list->content;
		if (!redir.file)
		{
			ft_putstr_fd("Minishell: ambiguous redirect\n", 2);
			return (1);
		}
		open_file = open(redir.file, get_open_flags(redir.type), 0664);
		if (open_file < 0)
		{
			file_error(redir.file, strerror(errno));
			return (1);
		}
		else
		{
			if (redir.type == 1 || redir.type == 4)
				dup2(open_file, STDOUT_FILENO);
			else
				dup2(open_file, STDIN_FILENO);
			close(open_file);
		}
		redir_list = redir_list->next;
	}
	return (0);
}

/*
** Cette fonction va decider a l'aide de istty si on utilse gnl ou get_input
*/

int	read_next_line(char **line, t_list *history, char *status)
{
	int		gnl_status;

	if (isatty(STDIN_FILENO))
		return (get_input_line(line, true, &history, status));
	else
	{
		gnl_status = ft_gnl(STDIN_FILENO, line);
		if (gnl_status < 0)
			file_error("STDIN_FILENO", strerror(errno));
		return (gnl_status);
	}
}

int	minishell(t_list **env_var, t_list *history)
{
	char	*line;
	int		ret;
	int		gnl_status;

	if (edit_var(env_var, "?", "0") == false)
		return (127);
	ret = 0;
	while (1)
	{
		gnl_status = read_next_line(&line, history, search_var(*env_var, "?"));
		if (gnl_status < 0)
			break ;
		if (!gnl_status)
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
	if (gnl_status >= 0)
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
