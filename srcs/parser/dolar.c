/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:24:03 by tmatis            #+#    #+#             */
/*   Updated: 2021/04/27 20:56:40 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Fais un split et le met dans une liste chainee
*/

t_list	*split_to_list(char *str)
{
	char	**split;
	int		i;
	t_list	*token_list;

	token_list = NULL;
	split = ft_split(str, ' ');
	if (!split)
		return (NULL);
	i = 0;
	while (split[i])
		ft_lstadd_back(&token_list, ft_lstnew(split[i++]));
	free(split);
	return (token_list);
}

/*
** Cherche la var dans l'env puis dans les locals
*/

char	*get_var(char *key, t_list *env_var, t_list *local_var)
{
	char	*search;

	search = search_var(env_var, key);
	if (search)
		return (search);
	search = search_var(local_var, key);
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

char	*dolar(char **str, t_list *env_var, t_list *local_var)
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
	value = ft_strdup(get_var(key, env_var, local_var));
	free(key);
	if (!value)
		return (ft_strdup(""));
	return (value);
}

/*
** Transforme la valeur en tokens et set selon les espace *concat
** concat :
**			0: first: YES | next: YES
**			1: first: NO | next: YES
**			2: first: YES | next: NO
**			3: first: NO | next: NO
*/

t_list	*dolar_tokenize(char **str, int *concat,
			t_list *env_var, t_list *local_var)
{
	char	*to_tokenize;
	t_list	*tokens;

	to_tokenize = dolar(str, env_var, local_var);
	if (to_tokenize[0] == ' ' && *concat < 1)
		(*concat) += 1;
	if (ft_strlen(to_tokenize)
		&& to_tokenize[ft_strlen(to_tokenize) - 1] == ' ' && *concat < 2)
		(*concat) += 2;
	tokens = split_to_list(to_tokenize);
	ft_safe_free(to_tokenize);
	if (ft_lstsize(tokens) == 0)
		ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("")));
	return (tokens);
}
