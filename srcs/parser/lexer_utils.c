/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 14:06:15 by tmatis            #+#    #+#             */
/*   Updated: 2021/06/04 13:03:07 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Fais un split et le met dans une liste chainee
*/

static char	**force_split(char **old_split)
{
	char	**split;

	free(old_split);
	split = ft_split(" ", '\0');
	if (!split)
		return (NULL);
	split[0][0] = '\0';
	return (split);
}

static t_bool	split_to_list(char *str, t_list **tokens, t_bool just_pipes)
{
	char	**split;
	int		i;
	t_list	*elem;

	split = ft_split(str, ' ');
	if (!just_pipes && split && !split[0])
		split = force_split(split);
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
	if (!split_to_list(to_tokenize, &tokens, append->just_pipes))
	{
		*error = LOG_ERROR;
		append->dollar_error = true;
		free(to_tokenize);
		return (NULL);
	}
	free(to_tokenize);
	return (tokens);
}

t_bool	append_dollar_token(t_list **dollar_tokens, t_list **tokens,
								t_list **to_join, int append)
{
	char	*token_str;
	t_list	*elem;

	if (append == START)
		token_str = ft_strdup((*dollar_tokens)->content);
	else
		token_str = ft_strdup((ft_lstlast(*dollar_tokens))->content);
	if (token_str)
		elem = ft_lstnew(token_str);
	if (!token_str || !elem)
	{
		ft_safe_free(token_str);
		ft_lstclear(to_join, ft_safe_free);
		ft_lstclear(dollar_tokens, ft_safe_free);
		ft_lstclear(tokens, ft_safe_free);
		return (false);
	}
	ft_lstadd_back(to_join, elem);
	if (append == START)
		ft_lstremove_first(dollar_tokens, ft_safe_free);
	else
		ft_lstremove_last(dollar_tokens, ft_safe_free);
	return (true);
}

t_bool	add_joint_tokens(t_list **dollar_tokens, t_list **tokens,
									t_list **to_join)
{
	char	*token_str;
	t_list	*elem;

	token_str = join_list(*to_join);
	if (token_str)
		elem = ft_lstnew(token_str);
	if (!token_str || !elem)
	{
		ft_safe_free(token_str);
		ft_lstclear(to_join, ft_safe_free);
		ft_lstclear(dollar_tokens, ft_safe_free);
		ft_lstclear(tokens, ft_safe_free);
		return (false);
	}
	ft_lstadd_back(tokens, elem);
	ft_lstclear(to_join, ft_safe_free);
	return (true);
}
