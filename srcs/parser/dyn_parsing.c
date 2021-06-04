/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dyn_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 14:12:28 by tmatis            #+#    #+#             */
/*   Updated: 2021/06/04 14:23:12 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Cree une liste de commande execute simultanement relier par des pipes
*/

static t_list	*pipes_commands(t_list *word_list, t_list *env_var)
{
	t_list		*pipes_list;
	int			special_id;
	t_command	*command;
	t_list		*elem;

	pipes_list = NULL;
	while (word_list)
	{
		special_id = escape_control(word_list->content);
		if (special_id == PIPE)
			word_list = word_list->next;
		if (special_id == SEMICOLON || !word_list)
			break ;
		command = get_command(&word_list, env_var);
		if (command)
			elem = ft_lstnew(command);
		if (!command || !elem)
		{
			ft_safe_free(command);
			ft_lstclear(&pipes_list, free_command);
			return (NULL);
		}
		ft_lstadd_back(&pipes_list, elem);
	}
	return (pipes_list);
}

static t_list	*get_next_pipes(char **str, int *error, t_list **env_var)
{
	t_list	*token_list;
	t_list	*pipes_list;

	token_list = tokenize(str, error, *env_var, true);
	if (*error != NO_ERROR)
	{
		write_error(*error);
		set_status_env(env_var, 2);
		return (NULL);
	}
	pipes_list = pipes_commands(token_list, *env_var);
	ft_lstclear(&token_list, ft_safe_free);
	if (!pipes_list && token_list)
	{
		ft_log_error(strerror(errno));
		set_status_env(env_var, 2);
		return (NULL);
	}
	return (pipes_list);
}

/*
** Fonction qui va call le tokensisateur et parse_commands et call l'exec
*/

int	exec_line(char *str, t_list **env_var)
{
	t_list		*word_list;
	t_list		*pipes_list;
	int			error;
	int			return_value;

	word_list = tokenize_all(str, &error, *env_var);
	error_detector(word_list, &error, env_var);
	ft_lstclear(&word_list, free);
	if (error != NO_ERROR)
		return (0);
	while (*str)
	{
		return_value = 0;
		pipes_list = get_next_pipes(&str, &error, env_var);
		if (!pipes_list && (!*str || error != NO_ERROR))
			return (0);
		if (pipes_list)
			return_value = exec(pipes_list, env_var);
		ft_lstclear(&pipes_list, free_command);
		if (return_value)
			return (return_value);
	}
	return (0);
}
