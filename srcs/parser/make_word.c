/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:49:46 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/17 12:33:10 by tmatis           ###   ########.fr       */
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
** Transforme la valeur en tokens et set selon les espace *concat
** concat :
**			0: first: YES | next: YES
**			1: first: NO | next: YES
**			2: first: YES | next: NO
**			3: first: NO | next: NO
*/

t_list	*dolar_tokenize(char **str, t_append *append,
			t_list *env_var)
{
	char	*to_tokenize;
	t_list	*tokens;

	to_tokenize = dolar(str, env_var);
	if (to_tokenize[0] == ' ')
		append->start = false;
	if (ft_strlen(to_tokenize)
		&& to_tokenize[ft_strlen(to_tokenize) - 1] == ' ')
		append->end = false;
	tokens = split_to_list(to_tokenize);
	ft_safe_free(to_tokenize);
	return (tokens);
}
/*
** Comportement du dolar savoir si on cat ou pas selon la valeur de concat
*/

static void	handle_dolar(t_list *dolar_tokens, t_list **tokens,
				t_list **to_cat, t_append *append)
{

}

/*
** Init les value pour gagner quelques ligne \O_O/
*/

static void	init_value(t_append *append, t_list **tokens, t_list **to_cat)
{
	append->start = true;
	append->end = true;
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
	t_append append;

	init_value(&append, &tokens, &to_cat);
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
			handle_dolar(dolar_tokenize(str, &append, env_var),
				&tokens, &to_cat, &append);
		else
			ft_lstadd_back(&to_cat, ft_lstnew(word(str)));
	}
	if (to_cat)
		ft_lstadd_back(&tokens, ft_lstnew(cat_list(to_cat)));
	ft_lstclear(&to_cat, ft_safe_free);
	return (tokens);
}
