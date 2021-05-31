/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:21:18 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/31 23:39:47 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Delimite un simple mot jusqu'a un char special
*/

char	*word(char **str)
{
	int		i;
	char	*word;

	i = 0;
	while ((*str)[i] && !ft_isspace((*str)[i]) && !is_special((*str) + i)
			&& (*str)[i] != '\'' && (*str)[i] != '"' && (*str)[i] != '$'
			&& (*str)[i] != '\\')
		i++;
	word = ft_substr(*str, 0, i);
	(*str) += i;
	return (word);
}

/*
** Prend une liste chainee avec content = str et cat en une seule string
*/

char	*join_list(t_list *to_cat)
{
	char	*dest;
	t_list	*temp;
	int		to_malloc;

	to_malloc = 0;
	temp = to_cat;
	while (temp && temp->content)
	{
		to_malloc += ft_strlen((char *)temp->content);
		temp = temp->next;
	}
	dest = ft_calloc(to_malloc + 1, sizeof(char));
	if (!dest)
		return (NULL);
	while (to_cat && to_cat->content)
	{
		ft_strcat(dest, (char *)to_cat->content);
		to_cat = to_cat->next;
	}
	return (dest);
}

static t_bool	add_special_str(t_list **word_list, char **str, int *error)
{
	char	*special_str;
	t_list	*elem;

	special_str = special(str);
	if (!special_str)
	{
		*error = LOG_ERROR;
		return (false);
	}
	elem = ft_lstnew(special_str);
	if (!elem)
	{
		free(special_str);
		*error = LOG_ERROR;
		return (false);
	}
	ft_lstadd_back(word_list, elem);
	return (true);
}

/*
** Tokenize tout ca pour le error check
*/

t_list	*tokenize(char **str, int *error, t_list *env_var, t_bool just_pipes)
{
	t_list	*word_list;
	t_list	*word_tokens;

	word_list = NULL;
	while (**str && (!just_pipes || **str != ';'))
	{
		if (is_special(*str))
			add_special_str(&word_list, str, error);
		else
		{
			word_tokens = make_word(str, error, env_var, just_pipes);
			ft_lstcat(&word_list, word_tokens);
			ft_lstclear(&word_tokens, ft_nofree);
		}
		if (*error == LOG_ERROR)
		{
			ft_lstclear(&word_list, ft_safe_free);
			break ;
		}
		while (ft_isspace(**str))
			(*str)++;
	}
	if (**str == ';')
		(*str)++;
	return (word_list);
}

t_list	*tokenize_all(char *str, int *error, t_list *env_var)
{
	*error = NO_ERROR;
	return (tokenize(&str, error, env_var, false));
}
