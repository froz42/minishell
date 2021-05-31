/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:24:03 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/31 23:46:09 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Cherche la var dans l'env puis dans les locals
*/

static char	*get_var(char *key, t_list *env_var)
{
	char	*search;

	search = search_var(env_var, key);
	if (search)
		return (ft_strdup(search));
	return (ft_strdup(""));
}

/*
** Retourne la cle selon les char et itere sur **str
*/

static char	*get_key(char **str, int *i)
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

char	*dollar(char **str, t_list *env_var)
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
	if (!key)
		return (NULL);
	if (i == 0)
	{
		ft_safe_free(key);
		return (ft_strdup("$"));
	}
	value = get_var(key, env_var);
	free(key);
	return (value);
}
