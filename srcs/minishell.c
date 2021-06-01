/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 14:59:37 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/31 23:19:52 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <termios.h>

/*
** Cette fonction va decider a l'aide de istty si on utilse gnl ou get_input
*/

static int	read_next_line(char **line, char **clipboard,
												t_list **history, char *status)
{
	int		left_to_read;

	if (isatty(STDIN_FILENO))
		return (get_input_line(line, clipboard, history, status));
	left_to_read = get_next_line(STDIN_FILENO, line);
	if (left_to_read < 0)
		file_error("STDIN_FILENO", strerror(errno));
	else if (left_to_read == 0 && (*line)[0] != '\0')
		left_to_read = 1;
	return (left_to_read);
}

static int	left_to_read_check(int left_to_read,
										int *ret, char *line, t_list **env_var)
{
	if (left_to_read < 0)
		return (1);
	if (!left_to_read)
	{
		*ret = ft_exit(1, NULL, env_var, false);
		return (1);
	}
	if (!line)
	{
		file_error("Alloc error", strerror(errno));
		return (1);
	}
	return (0);
}

int	minishell(t_list **env_var, t_list *history)
{
	char	*line;
	char	*clipboard;
	int		ret;
	int		left_to_read;

	clipboard = NULL;
	ret = 0;
	while (1)
	{
		left_to_read = read_next_line(&line, &clipboard,
				&history, search_var(*env_var, "?"));
		if (left_to_read_check(left_to_read, &ret, line, env_var))
			break ;
		ret = exec_line(line, env_var);
		if (ret)
			break ;
		free(line);
	}
	ft_lstclear(&history, free);
	ft_safe_free(clipboard);
	ft_safe_free(line);
	return (ret - IS_CHILD);
}
