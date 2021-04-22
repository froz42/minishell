/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 23:03:16 by tmatis            #+#    #+#             */
/*   Updated: 2021/04/22 13:28:13 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_list	*pipes_commands(t_list **word_list)
{
	t_list		*pipes_list;
	int			special;

	pipes_list = NULL;
	while (*word_list)
	{
		special = escape_control((*word_list)->content);
		if (special == 3)
			(*word_list) = (*word_list)->next;
		if (special == 5 || !*word_list)
			break ;
		ft_lstadd_back(&pipes_list, ft_lstnew(get_command(word_list)));
	}
	return (pipes_list);
}

t_list	*parse_commands(t_list *word_list)
{
	t_list		*commands_list;

	commands_list = NULL;
	while (word_list)
	{
		if (escape_control(word_list->content) == 5)
			word_list = word_list->next;
		if (!word_list)
			break;
		ft_lstadd_back(&commands_list, ft_lstnew(pipes_commands(&word_list)));
	}
	return (commands_list);
}

void	display_redirs(t_list *redir_list)
{
	t_redir *redir;

	printf("{");
	while (redir_list)
	{
		redir = redir_list->content;
		printf("{type = %i, file = %s}", redir->type, redir->file);
		redir_list = redir_list->next;
		if (redir_list)
			printf(", ");
	}
	printf("}\n");
}

void	display_args(t_list *args_list)
{
	printf("{");
	while (args_list)
	{
		printf("\"%s\"",(char *)args_list->content);
		args_list = args_list->next;
		if (args_list)
			printf(", ");
	}
	printf("}\n");
}

void	display_word(t_list *word)
{
	ft_putstr("{");
	while (word)
	{
		ft_putprintable((char *)word->content);
		word = word->next;
		if (word)
			ft_putstr(", ");
	}
	ft_putstr("}\n");
}


void	display_commands(t_list *commands_list)
{
	t_list		*pipes_list;
	t_command	cmd;

	printf("\n######COMMAND GRAPH######\n");
	printf("┌ t_list\n");
	while (commands_list)
	{
		pipes_list = commands_list->content;
		printf("│ • ┌ t_list\n");
		while (pipes_list)
		{
			printf("│   │ • ┌ t_command\n");
			cmd = *((t_command *)pipes_list->content);
			printf("│   │   │ • cmd = \"%s\"\n", cmd.cmd);
			printf("│   │   │ • args = ");
			display_args(cmd.args);
			printf("│   │   │ • redirs = ");
			display_redirs(cmd.redirs);
			pipes_list = pipes_list->next;
		}
		commands_list = commands_list->next;
	}
}

void	free_command_list(void *mem)
{
	t_list	*list;

	list = (t_list *)mem;
	ft_lstclear(&list, free_command);
}

void	parse_line(char *str)
{
	t_list		*word_list;
	t_list		*commands_list;
	int			error;

	error = -1;
	word_list = to_word(str, &error);
	if (error != -1)
		write_error(error);
	else
	{
		display_word(word_list);
		commands_list = parse_commands(word_list);
		display_commands(commands_list);
		ft_lstclear(&commands_list, free_command_list);
	}
	ft_lstclear(&word_list, free);
}
