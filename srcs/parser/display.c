/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:17:15 by tmatis            #+#    #+#             */
/*   Updated: 2021/04/27 20:51:45 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	display_redirs(t_list *redir_list)
{
	t_redir	*redir;

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

static void	display_args(t_list *args_list)
{
	printf("{");
	while (args_list)
	{
		printf("\"%s\"", (char *)args_list->content);
		args_list = args_list->next;
		if (args_list)
			printf(", ");
	}
	printf("}\n");
}

/*
** Permet d'afficher les tokens en remplacant les char non printable par '.'
*/

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

/*
** Affiche un graph des commandes (nice) pour le dev
*/

void	display_commands(t_list *commands_list)
{
	t_list		*pipes_list;
	t_command	cmd;

	printf("\n######COMMAND GRAPH######\n\n");
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
