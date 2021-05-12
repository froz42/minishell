/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:21:18 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/11 20:38:51 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Geres les char `; | >> > <` met un \33 (escape) devant
** pour les diff des user input
*/

char	*special(char **str)
{
	char	*token;

	token = ft_calloc(4, sizeof (char));
	if (!token)
		return (NULL);
	token[0] = '\33';
	if (is_special(*str) == 4)
	{
		ft_memcpy(token + 1, *str, 2);
		(*str) += 2;
	}
	else
	{
		ft_memcpy(token + 1, *str, 1);
		(*str) += 1;
	}
	return (token);
}

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

char	*cat_list(t_list *to_cat)
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
	dest = calloc(to_malloc + 1, sizeof(char));
	if (!dest)
		return (NULL);
	while (to_cat && to_cat->content)
	{
		ft_strcat(dest, (char *)to_cat->content);
		to_cat = to_cat->next;
	}
	return (dest);
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
			ft_lstadd_back(&word_list, ft_lstnew(special(str)));
		else if (**str)
		{
			word_tokens = make_word(str, error, env_var);
			ft_lstcat(&word_list, word_tokens);
			ft_lstclear(&word_tokens, ft_nofree);
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
	return (tokenize(&str, error, env_var, true));
}