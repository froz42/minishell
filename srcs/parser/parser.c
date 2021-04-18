/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 23:03:16 by tmatis            #+#    #+#             */
/*   Updated: 2021/04/18 13:08:58 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char *double_quote(char **str)
{
	int		i;
	char	*word;

	(*str)++;
	i = 0;
	word = NULL;
	while ((*str)[i] && (*str)[i] != '"')
		i++;
	if ((*str)[i] == '"')
	{
		word = ft_substr(*str, 0, i);
		(*str) += i + 1;
	}
	else
	{
		(*str) += i;
		ft_log_error("Double quote is not closed");
	}
	return (word);
}

char *single_quote(char **str)
{
	int		i;
	char	*word;

	(*str)++;
	i = 0;
	word = NULL;
	while ((*str)[i] && (*str)[i] != '\'')
		i++;
	if ((*str)[i] == '\'')
	{
		word = ft_substr(*str, 0, i);
		(*str) += i + 1;
	}
	else
	{
		(*str) += i;
		ft_log_error("single quote is not closed");
	}
	return (word);
}

int		is_special(char *str)
{
	int		strlen;

	strlen = ft_strlen(str);
	if (strlen >= 2 && !ft_memcmp(str, ">>", 2))
		return (4);
	if (*str == '>')
		return (1);
	if (*str == '<')
		return (2);
	if (*str == '|')
		return (3);
	if (*str == ';')
		return (5);
	return (0);
}

char	*special(char **str)
{
	char	*word;

	if (is_special(*str) == 4)
	{
		word = ft_substr(*str, 0, 2);
		(*str) += 2;
	}
	else
	{
		word = ft_substr(*str, 0, 1);
		(*str) += 1;
	}
	return (word);
}

char	*word(char **str)
{
	int		i;
	char	*word;

	i = 0;
	while ((*str)[i] && !ft_isspace((*str)[i]) && !is_special((*str) + i))
		i++;
	word = ft_substr(*str, 0, i);
	(*str) += i;
	return (word);
}

t_list	*to_word(char *str)
{
	t_list	*word_list;

	word_list = NULL;
	while (*str)
	{
		while (ft_isspace(*str))
			str++;
		if (*str == '"')
			ft_lstadd_back(&word_list, ft_lstnew(double_quote(&str)));
		else if (*str == '\'')
			ft_lstadd_back(&word_list, ft_lstnew(single_quote(&str)));
		else if (is_special(str))
			ft_lstadd_back(&word_list, ft_lstnew(special(&str)));
		else if (*str)
			ft_lstadd_back(&word_list, ft_lstnew(word(&str)));
	}
	return (word_list);
}

t_list	*pipes_commands(t_list **word_list)
{
	t_list		*pipes_list;
	int			special;

	pipes_list = NULL;
	while (*word_list)
	{
		special = is_special((*word_list)->content);
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
		if (is_special(word_list->content) == 5)
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

void	parse_line(char *str)
{
	t_list		*word_list;
	t_list		*commands_list;
	
	word_list = to_word(str);
	commands_list = parse_commands(word_list);
	display_commands(commands_list);
	ft_lstclear(&word_list, free);
}
