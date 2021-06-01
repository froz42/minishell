/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:49:46 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/31 23:34:05 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Comportement du dollar savoir si on cat ou pas selon la valeur de concat
*/

static int	handle_dollar(t_list **dollar_tokens, t_list **tokens,
								t_list **to_join, t_append *append)
{
	if (!*dollar_tokens && append->dollar_error)
	{
		ft_lstclear(to_join, ft_safe_free);
		ft_lstclear(tokens, ft_safe_free);
		return (LOG_ERROR);
	}
	else if (!*dollar_tokens)
		return (NO_ERROR);
	if (append->start)
		if (!append_dollar_token(dollar_tokens, tokens, to_join, START))
			return (LOG_ERROR);
	if (*dollar_tokens && *to_join)
		if (!add_joint_tokens(dollar_tokens, tokens, to_join))
			return (LOG_ERROR);
	if (append->end && *dollar_tokens)
		if (!append_dollar_token(dollar_tokens, tokens, to_join, END))
			return (LOG_ERROR);
	append->start = true;
	append->end = true;
	ft_lstcat(tokens, *dollar_tokens);
	ft_lstclear(dollar_tokens, ft_nofree);
	return (NO_ERROR);
}

/*
** Init les value pour gagner quelques ligne \O_O/
*/

static void	init_value(t_append *append, t_list **dollar_tokens,
							t_list **tokens, t_list **to_join)
{
	append->start = true;
	append->end = true;
	append->dollar_error = false;
	*dollar_tokens = NULL;
	*tokens = NULL;
	*to_join = NULL;
}

static t_bool	add_word(char **str, int *error,
							t_list *env_var, t_list **to_join)
{
	char	*word_str;
	t_list	*elem;

	if (**str == '"')
		word_str = make_double_quote(str, error, env_var);
	else if (**str == '\'')
		word_str = single_quote(str, error);
	else if (**str == '\\')
		word_str = backslash(str);
	else
		word_str = word(str);
	if (word_str)
		elem = ft_lstnew(word_str);
	if (!word_str || !elem)
	{
		ft_safe_free(word_str);
		ft_lstclear(to_join, ft_safe_free);
		if (*error == NO_ERROR)
			*error = LOG_ERROR;
		return (false);
	}
	ft_lstadd_back(to_join, elem);
	return (true);
}

/*
** Permet de tokeniser une suite de mot en correspondant a bash
*/

t_list	*make_word(char **str, int *error, t_list *env_var, t_bool just_pipes)
{
	t_append	append;
	t_list		*dollar_tokens;
	t_list		*tokens;
	t_list		*to_join;

	init_value(&append, &dollar_tokens, &tokens, &to_join);
	append.just_pipes = just_pipes;
	while (**str && !ft_isspace(**str) && !is_special(*str))
	{
		if (**str == '$')
		{
			dollar_tokens = dollar_tokenize(str, &append, error, env_var);
			*error = handle_dollar(&dollar_tokens, &tokens, &to_join, &append);
			if (*error != NO_ERROR)
				break ;
		}
		else if (!add_word(str, error, env_var, &to_join))
		{
			ft_lstclear(&tokens, ft_safe_free);
			break ;
		}
	}
	if (to_join)
		add_joint_tokens(&dollar_tokens, &tokens, &to_join);
	return (tokens);
}
