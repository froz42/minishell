/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:49:46 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/09 23:09:55 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Comportement du dolar savoir si on cat ou pas selon la valeur de concat
*/

static void	handle_dolar(t_list *dolar_tokens, t_list **tokens,
				t_list **to_cat, int *concat)
{
	if (*to_cat && (*concat == 0 || *concat == 2))
	{
		ft_lstadd_back(to_cat, ft_lstnew(ft_strdup(dolar_tokens->content)));
		ft_lstremove_first(&dolar_tokens, ft_safe_free);
	}
	if (*to_cat)
		ft_lstadd_back(tokens, ft_lstnew(cat_list(*to_cat)));
	ft_lstclear(to_cat, ft_safe_free);
	if (dolar_tokens && (*concat == 0 || *concat == 1))
	{
		ft_lstadd_back(to_cat,
			ft_lstnew(ft_strdup((ft_lstlast(dolar_tokens))->content)));
		ft_lstremove_last(&dolar_tokens, ft_safe_free);
		*concat = 0;
	}
	ft_lstcat(tokens, dolar_tokens);
	ft_lstclear(&dolar_tokens, ft_nofree);
}

/*
** Init les value pour gagner quelques ligne \O_O/
*/

static void	init_value(int *concat, t_list **tokens, t_list **to_cat)
{
	*concat = 0;
	*tokens = NULL;
	*to_cat = NULL;
}

/*
** Permet de tokeniser une suite de mot en correspondant a bash
*/

t_list	*make_word(char **str, int *error, t_list *env_var)
{
	t_list	*tokens;
	t_list	*to_cat;
	int		concat;

	init_value(&concat, &tokens, &to_cat);
	while (**str && !ft_isspace(**str) && !is_special(*str))
	{
		if (**str == '"')
			ft_lstadd_back(&to_cat,
				ft_lstnew(make_double_quote(str, error, env_var)));
		else if (**str == '\'')
			ft_lstadd_back(&to_cat, ft_lstnew(single_quote(str, error)));
		else if (**str == '\\')
			ft_lstadd_back(&to_cat, ft_lstnew(backslash(str)));
		else if (**str == '$')
			handle_dolar(dolar_tokenize(str, &concat, env_var),
				&tokens, &to_cat, &concat);
		else
			ft_lstadd_back(&to_cat, ft_lstnew(word(str)));
	}
	if (to_cat)
		ft_lstadd_back(&tokens, ft_lstnew(cat_list(to_cat)));
	ft_lstclear(&to_cat, ft_safe_free);
	return (tokens);
}
