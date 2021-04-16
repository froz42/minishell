/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 23:03:16 by tmatis            #+#    #+#             */
/*   Updated: 2021/04/16 15:38:38 by tmatis           ###   ########.fr       */
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

void	parse_command(t_list *word_list)
{
	t_command	*command;

	command = get_command(&word_list);
	printf("cmd: %s\nargs_size: %i\nredir_size: %i\n", command->cmd, ft_lstsize(command->args), ft_lstsize(command->redirs));
	free_command(command);
}

void	parse_line(char *str)
{
	t_list		*word_list;

	word_list = to_word(str);
	parse_command(word_list);
	ft_lstclear(&word_list, free);
}
