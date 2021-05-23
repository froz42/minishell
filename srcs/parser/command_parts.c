/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parts.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 14:31:45 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/23 14:34:27 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Parse a potential redirection, iter on word_list
*/

t_redir	*get_redir(t_list **word_list, int special_id)
{
	t_redir		*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = special_id;
	redir->file = NULL;
	*word_list = (*word_list)->next;
	if (*word_list)
	{
		special_id = escape_control((*word_list)->content);
		if (special_id != SEMICOLON && special_id != PIPE)
		{
			redir->file = ft_strdup((*word_list)->content);
			if (!redir->file)
			{
				free(redir);
				return (NULL);
			}
			*word_list = (*word_list)->next;
		}
	}
	return (redir);
}

/*
** Set the command in the struct
*/

t_bool	set_command(t_list	**word_list, t_command *command,
										t_list *env_var)
{
	command->name = ft_strdup((*word_list)->content);
	if (!command->name || !find_bin(command, env_var))
	{
		free_command(command);
		return (false);
	}
	command->is_set = true;
	*word_list = (*word_list)->next;
	return (true);
}

/*
** Retourne l'argument et passe au suivant
*/

char	*get_arg(t_list **word_list)
{
	char	*dst;

	dst = ft_strdup((*word_list)->content);
	*word_list = (*word_list)->next;
	return (dst);
}
