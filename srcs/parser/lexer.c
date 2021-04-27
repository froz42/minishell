/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:21:18 by tmatis            #+#    #+#             */
/*   Updated: 2021/04/27 17:14:56 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*special(char **str)
{
	char	*word;

	word = ft_calloc(4, sizeof (char));
	if (!word)
		return (NULL);
	word[0] = '\33';
	if (is_special(*str) == 4)
	{
		ft_memcpy(word + 1, *str, 2);
		(*str) += 2;
	}
	else
	{
		ft_memcpy(word + 1, *str, 1);
		(*str) += 1;
	}
	return (word);
}

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
** concat :
**			0: first: YES | next: YES
**			1: first: NO | next: YES
**			2: first: YES | next: NO
**			3: first: NO | next: NO
*/

t_list	*to_word(char *str, int *error, t_list *env_var, t_list *local_var)
{
	t_list	*word_list;
	t_list	*word_tokens;

	word_list = NULL;
	while (*str)
	{
		while (ft_isspace(*str))
			str++;
		if (is_special(str))
			ft_lstadd_back(&word_list, ft_lstnew(special(&str)));
		else if (*str)
		{
			word_tokens = make_word(&str, error, env_var, local_var);
			ft_lstcat(&word_list, word_tokens);
			ft_lstclear(&word_tokens, ft_nofree);
		}
	}
	return (word_list);
}
