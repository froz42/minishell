/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:21:18 by tmatis            #+#    #+#             */
/*   Updated: 2021/04/22 13:05:28 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char *double_quote(char **str, int *error)
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
		*error = 0;
	}
	return (word);
}

char *single_quote(char **str, int *error)
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
		*error = 0;
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

	word = ft_calloc(4, sizeof (char));
	word[0] = '\33';
	if (!word)
		return (NULL);
	if (is_special(*str) == 4)
	{
		ft_memcpy(word + 1, *str, 2);
		(*str) += 2;
	}
	else
	{
		ft_memcpy(word + 1, *str, 1);
		(*str) += 1;
	}
	return (word);
}

char	*word(char **str)
{
	int		i;
	char	*word;

	i = 0;
	while ((*str)[i] && !ft_isspace((*str)[i]) && !is_special((*str) + i)
			&& (*str)[i] != '\'' && (*str)[i] != '"')
		i++;
	word = ft_substr(*str, 0, i);
	(*str) += i;
	return (word);
}

char	*cat_list(t_list *to_cat)
{
	char	*dest;
	t_list	*temp;
	int		to_malloc;

	to_malloc = 0;
	temp = to_cat;
	while (temp && temp->content)
	{
		to_malloc += ft_strlen((char *)temp->content);
		temp = temp->next;
	}
	dest = calloc(to_malloc + 1, sizeof(char));
	if (!dest)
		return (NULL);
	while (to_cat && to_cat->content)
	{
		ft_strcat(dest, (char *)to_cat->content);
		to_cat = to_cat->next;
	}
	return (dest);
}

char	*make_word(char **str, int *error)
{
	t_list	*to_cat;
	char	*dest;

	to_cat = NULL;
	while (**str && !ft_isspace(**str) && !is_special(*str))
	{
		if (**str == '"')
			ft_lstadd_back(&to_cat, ft_lstnew(double_quote(str, error)));
		else if (**str == '\'')
			ft_lstadd_back(&to_cat, ft_lstnew(single_quote(str, error)));
		else
			ft_lstadd_back(&to_cat, ft_lstnew(word(str)));
	}
	dest = cat_list(to_cat);
	ft_lstclear(&to_cat, ft_safe_free);
	return (dest);
}

t_list	*to_word(char *str, int *error)
{
	t_list	*word_list;

	word_list = NULL;
	while (*str)
	{
		while (ft_isspace(*str))
			str++;
		if (is_special(str))
			ft_lstadd_back(&word_list, ft_lstnew(special(&str)));
		else if (*str)
			ft_lstadd_back(&word_list, ft_lstnew(make_word(&str, error)));
	}
	return (word_list);
}

