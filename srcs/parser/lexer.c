/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:21:18 by tmatis            #+#    #+#             */
/*   Updated: 2021/04/23 12:43:09 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char *get_var(char *key, t_list *env_var, t_list *local_var)
{
	char *search;

	search = search_var(env_var, key);
	if (search)
		return (search);
	search = search_var(local_var, key);
	if (search)
		return (search);
	return ("");
}

char *dolar(char **str, t_list *env_var, t_list *local_var)
{
	int		i;
	char	*key;
	char	*value;

	(*str) += 1;
	if (ft_isnum(**str))
	{
		(*str) += 1;
		return (ft_strdup(""));
	}
	i = 0;
	while ((*str)[i] && ((*str)[i] == '_' || ft_isalnum((*str)[i])))
		i++;
	if (i == 0)
		return (ft_strdup("$"));
	key = ft_substr(*str, 0, i);
	(*str) += i;
	if (!key)
		return (NULL);
	value = ft_strdup(get_var(key, env_var, local_var));
	free(key);
	if (!value)
		return (ft_strdup(""));
	return (value);
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
	if (!word)
		return (NULL);
	word[0] = '\33';
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
			&& (*str)[i] != '\'' && (*str)[i] != '"' && (*str)[i] != '$')
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

char *double_quote(char **str)
{
	int		i;
	char	*word;

	i = 0;
	word = NULL;
	while ((*str)[i] && (*str)[i] != '"' && (*str)[i] != '$')
		i++;
	word = ft_substr(*str, 0, i);
	(*str) += i;
	return (word);
}

char	*make_double_quote(char **str, int *error, t_list *env_var, t_list *local_var)
{
	t_list	*to_cat;
	char	*dest;

	(*str) += 1;
	to_cat = NULL;
	while (**str && **str != '"')
	{
		if (**str == '$')
			ft_lstadd_back(&to_cat, ft_lstnew(dolar(str, env_var, local_var)));
		else
			ft_lstadd_back(&to_cat, ft_lstnew(double_quote(str)));
	}
	dest = cat_list(to_cat);
	ft_lstclear(&to_cat, ft_safe_free);
	if (**str == '"')
	{
		(*str) += 1;
		return (dest);
	}
	else
	{
		*error = 0;
		ft_safe_free(dest);
		return (NULL);
	}
}

char	*make_word(char **str, int *error, t_list *env_var, t_list *local_var)
{
	t_list	*to_cat;
	char	*dest;

	to_cat = NULL;
	while (**str && !ft_isspace(**str) && !is_special(*str))
	{
		if (**str == '"')
			ft_lstadd_back(&to_cat, ft_lstnew(make_double_quote(str, error, env_var, local_var)));
		else if (**str == '\'')
			ft_lstadd_back(&to_cat, ft_lstnew(single_quote(str, error)));
		else if (**str == '$')
			ft_lstadd_back(&to_cat, ft_lstnew(dolar(str, env_var, local_var)));
		else
			ft_lstadd_back(&to_cat, ft_lstnew(word(str)));
	}
	dest = cat_list(to_cat);
	ft_lstclear(&to_cat, ft_safe_free);
	return (dest);
}

t_list	*to_word(char *str, int *error, t_list *env_var, t_list *local_var)
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
			ft_lstadd_back(&word_list, ft_lstnew(make_word(&str, error, env_var, local_var)));
	}
	return (word_list);
}

