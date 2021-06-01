/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:26:42 by tmatis            #+#    #+#             */
/*   Updated: 2021/06/01 12:12:04 by tmatis           ###   ########.fr       */
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
	int		has_single_quote;

	(*str)++;
	has_single_quote = 0;
	token = NULL;
	i = 0;
	while ((*str)[i] && (*str)[i] != '\'')
		i++;
	if ((*str)[i] == '\'')
	{
		token = ft_substr(*str, 0, i);
		has_single_quote = 1;
	}
	else
		*error = SING_QUOTE_ERR;
	(*str) += i + has_single_quote;
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
		dest = ft_calloc(2, sizeof(char));
		if (!dest)
			return (NULL);
		dest[0] = **str;
	}
	else
	{
		dest = ft_calloc(3, sizeof(char));
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
