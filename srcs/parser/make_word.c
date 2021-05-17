/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:49:46 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/17 13:41:26 by tmatis           ###   ########.fr       */
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
** Transforme la valeur en tokens et set selon les espace append
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
	if (ft_lstsize(tokens) == 0)
		ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("")));
	ft_safe_free(to_tokenize);
	return (tokens);
}
/*
** Comportement du dolar savoir si on cat ou pas selon la valeur de concat
*/

static void	handle_dolar(t_list *dolar_tokens, t_list **tokens,
				t_list **to_join, t_append *append)
{
	if (append->start)
	{
		ft_lstadd_back(to_join, ft_lstnew(ft_strdup(dolar_tokens->content)));
		ft_lstremove_first(&dolar_tokens, ft_safe_free);
	}
	if (dolar_tokens && *to_join)
	{
		ft_lstadd_back(tokens, ft_lstnew(join_list(*to_join)));
		ft_lstclear(to_join, ft_safe_free);
	}

}

/*
** Init les value pour gagner quelques ligne \O_O/
*/

static void	init_value(t_append *append, t_list **tokens, t_list **to_join)
{
	append->start = true;
	append->end = true;
	*tokens = NULL;
	*to_join = NULL;
}

/*
** Permet de tokeniser une suite de mot en correspondant a bash
*/

t_list	*make_word(char **str, int *error, t_list *env_var)
{
	t_list	*tokens;
	t_list	*to_join;
	t_append append;

	init_value(&append, &tokens, &to_join);
	while (**str && !ft_isspace(**str) && !is_special(*str))
	{
		if (**str == '"')
			ft_lstadd_back(&to_join,
				ft_lstnew(make_double_quote(str, error, env_var)));
		else if (**str == '\'')
			ft_lstadd_back(&to_join, ft_lstnew(single_quote(str, error)));
		else if (**str == '\\')
			ft_lstadd_back(&to_join, ft_lstnew(backslash(str)));
		else if (**str == '$')
			handle_dolar(dolar_tokenize(str, &append, env_var),
				&tokens, &to_join, &append);
		else
			ft_lstadd_back(&to_join, ft_lstnew(word(str)));
	}
	if (to_join)
		ft_lstadd_back(&tokens, ft_lstnew(join_list(to_join)));
	ft_lstclear(&to_join, ft_safe_free);
	return (tokens);
}
