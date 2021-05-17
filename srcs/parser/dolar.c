/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:24:03 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/17 13:38:54 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Cherche la var dans l'env puis dans les locals
*/

char	*get_var(char *key, t_list *env_var)
{
	char	*search;

	search = search_var(env_var, key);
	if (search)
		return (search);
	return ("");
}

/*
** Retourne la cle selon les char et itere sur **str
*/

char	*get_key(char **str, int *i)
{
	char	*key;

	if (**str == '?')
	{
		*i = 1;
		(*str) += *i;
		return (ft_strdup("?"));
	}
	*i = 0;
	while ((*str)[*i] && ((*str)[*i] == '_' || ft_isalnum((*str)[*i])))
		(*i)++;
	key = ft_substr(*str, 0, *i);
	(*str) += *i;
	return (key);
}

/*
** Retourne la valeur du $ au bon format
*/

char	*dolar(char **str, t_list *env_var)
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
	key = get_key(str, &i);
	if (i == 0)
		return (ft_strdup("$"));
	if (!key)
		return (NULL);
	value = ft_strdup(get_var(key, env_var));
	free(key);
	if (!value)
		return (ft_strdup(""));
	return (value);
}
