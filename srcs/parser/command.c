/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 15:28:01 by tmatis            #+#    #+#             */
/*   Updated: 2021/06/01 00:02:47 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Init the command structure
*/

static t_command	*init_command(void)
{
	t_command	*command;

	command = ft_calloc(1, sizeof(t_command));
	if (!command)
		return (NULL);
	command->is_set = false;
	return (command);
}

static t_bool	find_redir(t_list **word_list, int special_id,
														t_command *command)
{
	t_redir		*redir;
	t_list		*elem;

	redir = get_redir(word_list, special_id);
	if (redir)
		elem = ft_lstnew(redir);
	if (!redir || !elem)
	{
		free_redir(redir);
		free_command(command);
		return (false);
	}
	ft_lstadd_back(&command->redirs, elem);
	return (true);
}

static t_bool	find_arg(t_list **word_list, t_command *command)
{
	char	*arg;
	t_list	*elem;

	arg = get_arg(word_list);
	if (arg)
		elem = ft_lstnew(arg);
	if (!arg || !elem)
	{
		ft_safe_free(arg);
		free_command(command);
		return (false);
	}
	ft_lstadd_back(&command->args, elem);
	return (true);
}

/*
** retourne l'objet t_command en utilisant les tokens
** jusqu'a rencontrer un token | ou ;
** le premier token a ne pas etre une redirection est considere
** comme la commande
*/

t_command	*get_command(t_list **word_list, t_list *env_var)
{
	t_command	*command;
	int			token_id;

	command = init_command();
	if (!command)
		return (NULL);
	while (*word_list)
	{
		token_id = escape_control((*word_list)->content);
		if (token_id == SEMICOLON || token_id == PIPE)
			break ;
		if (token_id == REDIR_OUT || token_id == REDIR_IN || token_id == APPEND)
		{
			if (!find_redir(word_list, token_id, command))
				return (NULL);
		}
		else if (!command->is_set)
		{
			if (!set_command(word_list, command, env_var))
				return (NULL);
		}
		else if (!find_arg(word_list, command))
			return (NULL);
	}
	return (command);
}
