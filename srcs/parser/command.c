/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 15:28:01 by tmatis            #+#    #+#             */
/*   Updated: 2021/04/22 12:51:06 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_command	*init_command(void)
{
	t_command	*command;

	command = calloc(1, sizeof(t_command));
	if (!command)
		return (NULL);
	return (command);
}

void				free_redir(void *mem)
{
	t_redir	*redir;

	if (mem)
	{
		redir = (t_redir *)mem;
		if (redir->file)
			free(redir->file);
		free(mem);
	}
}

void				free_command(void *mem)
{
	t_command	*command;

	command = (t_command *)mem;
	free(command->cmd);
	ft_lstclear(&command->args, ft_safe_free);
	ft_lstclear(&command->redirs, free_redir);
	free(command);
}

int	escape_control(char *str)
{
	if (*str == '\33')
		return (is_special(str + 1));
	else
		return (0);
}

static t_redir		*get_redir(t_list **word_list)
{
	t_redir		*redir;
	int			special;

	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = escape_control((*word_list)->content);
	*word_list = (*word_list)->next;
	if (*word_list)
	{
		special = escape_control((*word_list)->content);
		if (special != 5 && special != 3)
		{
			redir->file = ft_strdup((*word_list)->content);
			*word_list = (*word_list)->next;
		}
	}
	else
		redir->file = NULL;
	return (redir);
}


static void		set_command(t_list	**word_list, t_command *command)
{
	command->cmd = ft_strdup((*word_list)->content);
	*word_list = (*word_list)->next;
}

static char	*get_arg(t_list **word_list)
{
	char	*dst;

	dst = ft_strdup((*word_list)->content);
	*word_list = (*word_list)->next;
	return (dst);
}

t_command	*get_command(t_list **word_list)
{
	t_command	*command;
	t_bool		command_set;
	int			special;

	command = init_command();
	command_set = false;
	if (!command)
		return (NULL);
	while (*word_list)
	{
		special = escape_control((*word_list)->content);
		if (special == 5 || special == 3)
			break ;
		if (special == 1 || special == 2 || special == 4)
			ft_lstadd_back(&command->redirs, ft_lstnew(get_redir(word_list)));
		else if (!command_set)
		{
			command_set = true;
			set_command(word_list, command);
		}
		else
			ft_lstadd_back(&command->args, ft_lstnew(get_arg(word_list)));
	}
	return (command);
}
