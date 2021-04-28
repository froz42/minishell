/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:26:42 by tmatis            #+#    #+#             */
/*   Updated: 2021/04/28 16:46:53 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Gere le contenu des single quote
*/

char	*single_quote(char **str, int *error)
{
	int		i;
	char	*token;

	(*str)++;
	i = 0;
	token = NULL;
	while ((*str)[i] && (*str)[i] != '\'')
		i++;
	if ((*str)[i] == '\'')
	{
		token = ft_substr(*str, 0, i);
		(*str) += i + 1;
	}
	else
	{
		(*str) += i;
		*error = 0;
	}
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

/*
** Retourne le str de l'interieur des double quote
** EX "Hello $USER you have 10\$" -> "Hello tmatis you have 10$"
*/

char	*make_double_quote(char **str, int *error,
			t_list *env_var)
{
	t_list	*to_cat;
	char	*dest;

	(*str) += 1;
	to_cat = NULL;
	while (**str && **str != '"')
	{
		if (**str == '$')
			ft_lstadd_back(&to_cat, ft_lstnew(dolar(str, env_var)));
		else if (**str == '\\')
			ft_lstadd_back(&to_cat, ft_lstnew(backslash_double_quote(str)));
		else
			ft_lstadd_back(&to_cat, ft_lstnew(double_quote(str)));
	}
	dest = cat_list(to_cat);
	ft_lstclear(&to_cat, ft_safe_free);
	if (**str == '"')
		(*str) += 1;
	else
		*error = 0;
	return (dest);
}
