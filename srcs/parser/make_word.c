/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:49:46 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/18 20:50:11 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Fais un split et le met dans une liste chainee
*/

char	**force_split(void)
{
	char	**split;

	split = ft_split(" ", '\0');
	if (!split)
		return (NULL);
	split[0][0] = '\0';
	return (split);
}

t_bool	split_to_list(char *str, t_list **tokens)
{
	char	**split;
	int		i;
	t_list	*elem;

	split = ft_split(str, ' ');
	if (split && !split[0])
		split = force_split();
	if (!split)
		return (false);
	i = -1;
	while (split[++i])
	{
		elem = ft_lstnew(split[i]);
		if (!elem)
		{
			ft_lstclear(tokens, free);
			while (split[i])
				free(split[i++]);
			free(split);
			return (false);
		}
		ft_lstadd_back(tokens, elem);
	}
	free(split);
	return (true);
}

/*
** Transforme la valeur en tokens et set selon les espace append
*/

t_list	*dollar_tokenize(char **str, t_append *append,
							int *error, t_list *env_var)
{
	char	*to_tokenize;
	t_list	*tokens;

	to_tokenize = dollar(str, env_var);
	if (!to_tokenize)
		return (NULL);
	if (to_tokenize[0] == ' ')
		append->start = false;
	if (*to_tokenize && to_tokenize[ft_strlen(to_tokenize) - 1] == ' ')
		append->end = false;
	tokens = NULL;
	if (!split_to_list(to_tokenize, &tokens))
	{
		*error = LOG_ERROR;
		free(to_tokenize);
		return (NULL);
	}
	free(to_tokenize);
	return (tokens);
}

/*
** Comportement du dollar savoir si on cat ou pas selon la valeur de concat
*/

static void	handle_dollar(t_list *dollar_tokens, t_list **tokens,
							t_list **to_join, t_append *append)
{
	if (append->start)
	{
		ft_lstadd_back(to_join, ft_lstnew(ft_strdup(dollar_tokens->content)));
		ft_lstremove_first(&dollar_tokens, ft_safe_free);
	}
	if (dollar_tokens && *to_join)
	{
		ft_lstadd_back(tokens, ft_lstnew(join_list(*to_join)));
		ft_lstclear(to_join, ft_safe_free);
	}
	if (append->end && dollar_tokens)
	{
		ft_lstadd_back(to_join, ft_lstnew(ft_strdup(ft_lstlast(dollar_tokens)->content)));
		ft_lstremove_last(&dollar_tokens, ft_safe_free);
	}
	append->start = true;
	append->end = true;
	ft_lstcat(tokens, dollar_tokens);
	ft_lstclear(&dollar_tokens, ft_nofree);
}

/*
** Init les value pour gagner quelques ligne \O_O/
*/

static void	init_value(t_append *append, t_list ** dollar_tokens,
							t_list **tokens, t_list **to_join)
{
	append->start = true;
	append->end = true;
	*dollar_tokens = NULL;
	*tokens = NULL;
	*to_join = NULL;
}

t_bool	add_word(char **str, int *error, t_list *env_var, t_list **to_join)
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

t_list	*make_word(char **str, int *error, t_list *env_var)
{
	t_append append;
	t_list	*dollar_tokens;
	t_list	*tokens;
	t_list	*to_join;

	init_value(&append, &dollar_tokens, &tokens, &to_join);
	while (**str && !ft_isspace(**str) && !is_special(*str))
	{
		if (**str == '$')
		{
			dollar_tokens = dollar_tokenize(str, &append, error, env_var);
			if (!dollar_tokens)
				break ;
			handle_dollar(dollar_tokens, &tokens, &to_join, &append);
		}
		else if (!add_word(str, error, env_var, &to_join))
			break ;
	}
	if (to_join)
		ft_lstadd_back(&tokens, ft_lstnew(join_list(to_join)));
	ft_lstclear(&to_join, ft_safe_free);
	return (tokens);
}
