/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:26:42 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/19 17:15:21 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Gere le contenu des single quote
*/

char	*single_quote(char **str, int *error)
{
	char	*token;
	int		i;

	(*str)++;
	token = NULL;
	i = 0;
	while ((*str)[i] && (*str)[i] != '\'')
		i++;
	if ((*str)[i] == '\'')
	{
		token = ft_substr(*str, 0, i);
		(*str) += i + 1;
	}
	else
		*error = SING_QUOTE_ERR;
	return (token);
}

/*
** comportement du \ dans les ""
*/

char	*backslash_double_quote(char **str)
{
	char	*dest;

	(*str) += 1;
	if (**str == '$' || **str == '\\' || **str == '"')
	{
		dest = calloc(2, sizeof(char));
		if (!dest)
			return (NULL);
		dest[0] = **str;
	}
	else
	{
		dest = calloc(3, sizeof(char));
		if (!dest)
			return (NULL);
		dest[0] = '\\';
		dest[1] = **str;
	}
	if (**str)
		(*str) += 1;
	return (dest);
}

/*
** comportement du \
*/

char	*backslash(char **str)
{
	char	*dest;

	(*str) += 1;
	dest = ft_calloc(2, sizeof(char));
	if (!dest)
		return (NULL);
	dest[0] = **str;
	if (**str)
		(*str) += 1;
	return (dest);
}

/*
** Gere le comportement des double quote s'arrete
** en cas de char special
*/

char	*double_quote(char **str)
{
	int		i;
	char	*token;

	i = 0;
	token = NULL;
	while ((*str)[i] && (*str)[i] != '"' && (*str)[i] != '$'
			&& (*str)[i] != '\\')
		i++;
	token = ft_substr(*str, 0, i);
	(*str) += i;
	return (token);
}

t_bool	add_db_quote_word(char **str, t_list *env_var, t_list **to_join)
{
	char	*word_str;
	t_list	*elem;

	if (**str == '$')
		word_str = dollar(str, env_var);
	else if (**str == '\\')
		word_str = backslash_double_quote(str);
	else
		word_str = double_quote(str);
	if (word_str)
		elem = ft_lstnew(word_str);
	if (!word_str || !elem)
	{
		ft_safe_free(word_str);
		ft_lstclear(to_join, ft_safe_free);
		return (false);
	}
	ft_lstadd_back(to_join, elem);
	return (true);
}

/*
** Retourne le str de l'interieur des double quote
** EX "Hello $USER you have 10\$" -> "Hello tmatis you have 10$"
*/

char	*make_double_quote(char **str, int *error, t_list *env_var)
{
	t_list	*to_join;
	char	*dest;

	(*str) += 1;
	to_join = NULL;
	while (**str && **str != '"')
		if (!add_db_quote_word(str, env_var, &to_join))
			return (NULL);
	dest = join_list(to_join);
	ft_lstclear(&to_join, ft_safe_free);
	if (!dest)
		return (NULL);
	if (**str != '"')
	{
		free(dest);
		*error = DB_QUOTE_ERR;
		return (NULL);
	}
	(*str) += 1;
	return (dest);
}
