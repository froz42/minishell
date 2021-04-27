/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:21:18 by tmatis            #+#    #+#             */
/*   Updated: 2021/04/27 15:36:41 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char *get_var(char *key, t_list *env_var, t_list *local_var)
{
	char *search;

	search = search_var(env_var, key);
	if (search)
		return (search);
	search = search_var(local_var, key);
	if (search)
		return (search);
	return ("");
}

char *get_key(char **str, int *i)
{
	char	*key;

	*i = 0;
	while ((*str)[*i] && ((*str)[*i] == '_' || ft_isalnum((*str)[*i])))
		(*i)++;
	key = ft_substr(*str, 0, *i);
	(*str) += *i;
	return (key);
}

char *dolar(char **str, t_list *env_var, t_list *local_var)
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

char *single_quote(char **str, int *error)
{
	int		i;
	char	*word;

	(*str)++;
	i = 0;
	word = NULL;
	while ((*str)[i] && (*str)[i] != '\'')
		i++;
	if ((*str)[i] == '\'')
	{
		word = ft_substr(*str, 0, i);
		(*str) += i + 1;
	}
	else
	{
		(*str) += i;
		*error = 0;
	}
	return (word);
}

int		is_special(char *str)
{
	int		strlen;

	strlen = ft_strlen(str);
	if (strlen >= 2 && !ft_memcmp(str, ">>", 2))
		return (4);
	if (*str == '>')
		return (1);
	if (*str == '<')
		return (2);
	if (*str == '|')
		return (3);
	if (*str == ';')
		return (5);
	return (0);
}

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

char *double_quote(char **str)
{
	int		i;
	char	*word;

	i = 0;
	word = NULL;
	while ((*str)[i] && (*str)[i] != '"' && (*str)[i] != '$'
			&& (*str)[i] != '\\')
		i++;
	word = ft_substr(*str, 0, i);
	(*str) += i;
	return (word);
}

char	*backslash_double_quote(char **str)
{
	char *dest;

	(*str) += 1;
	if (**str == '$' || **str == '\\' || **str == '"')
	{
		dest = calloc(2, sizeof(char));
		if (!dest)
			return (NULL);
		dest[0] = **str;
	}
	else
	{
		dest = calloc(3, sizeof(char));
		if (!dest)
			return (NULL);
		dest[0] = '\\';
		dest[1] = **str;
	}
	if (**str)
		(*str) += 1;
	return (dest);
}

char	*make_double_quote(char **str, int *error, t_list *env_var, t_list *local_var)
{
	t_list	*to_cat;
	char	*dest;

	(*str) += 1;
	to_cat = NULL;
	while (**str && **str != '"')
	{
		if (**str == '$')
			ft_lstadd_back(&to_cat, ft_lstnew(dolar(str, env_var, local_var)));
		else if (**str == '\\')
			ft_lstadd_back(&to_cat, ft_lstnew(backslash_double_quote(str)));
		else
			ft_lstadd_back(&to_cat, ft_lstnew(double_quote(str)));
	}
	dest = cat_list(to_cat);
	ft_lstclear(&to_cat, ft_safe_free);
	if (**str == '"')
		(*str) += 1;
	else
		*error = 0;
	return (dest);
}

char	*backslash(char **str)
{
	char *dest;

	(*str) += 1;
	dest = ft_calloc(2, sizeof(char));
	if (!dest)
		return (NULL);
	dest[0] = **str;
	if (**str)
		(*str) += 1;
	return (dest);
}


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


t_list	*dolar_tokenize(char **str, int *concat, t_list *env_var, t_list *local_var)
{
	char	*to_tokenize;
	t_list	*tokens;
	
	to_tokenize = dolar(str, env_var, local_var);
	printf("to token |%s|\n", to_tokenize);
	if (to_tokenize[0] == ' ' && *concat < 1)
		(*concat) += 1;
	if (to_tokenize[ft_strlen(to_tokenize) - 1] == ' ' && *concat < 2)
		(*concat) += 2;
	tokens = split_to_list(to_tokenize);
	ft_safe_free(to_tokenize);
	if (ft_lstsize(tokens) == 0)
		ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("")));
	return (tokens);
}

/*
** concat :
**			0: first: YES | next: YES
**			1: first: NO | next: YES
**			2: first: YES | next: NO
**			3: first: NO | next: NO
*/

t_list	*make_word(char **str, int *error, t_list *env_var, t_list *local_var)
{
	t_list	*tokens;
	t_list	*to_cat;
	t_list	*dolar_tokens;
	int		concat;

	concat = 0;
	tokens = NULL;
	to_cat = NULL;
	while (**str && !ft_isspace(**str) && !is_special(*str))
	{
		if (**str == '"')
			ft_lstadd_back(&to_cat, ft_lstnew(make_double_quote(str, error, env_var, local_var)));
		else if (**str == '\'')
			ft_lstadd_back(&to_cat, ft_lstnew(single_quote(str, error)));
		else if (**str == '\\')
			ft_lstadd_back(&to_cat, ft_lstnew(backslash(str)));
		else if (**str == '$')
		{
			dolar_tokens = dolar_tokenize(str, &concat, env_var, local_var);
			printf("concat value: %i\n", concat);
			if (to_cat && (concat == 0 || concat == 2))
			{
				ft_lstadd_back(&to_cat, ft_lstnew(ft_strdup(dolar_tokens->content)));
				ft_lstremove_first(&dolar_tokens, ft_safe_free);
			}
			if (to_cat)
				ft_lstadd_back(&tokens, ft_lstnew(cat_list(to_cat)));
			ft_lstclear(&to_cat, ft_safe_free);
			if (dolar_tokens && (concat == 0 || concat == 1))
			{
				ft_lstadd_back(&to_cat, ft_lstnew(ft_strdup((ft_lstlast(dolar_tokens))->content)));
				ft_lstremove_last(&dolar_tokens, ft_safe_free);
				concat = 0;
			}
			ft_lstcat(&tokens, dolar_tokens);
			ft_lstclear(&dolar_tokens, ft_nofree);
		}
		else
			ft_lstadd_back(&to_cat, ft_lstnew(word(str)));
	}
	if (to_cat)
		ft_lstadd_back(&tokens, ft_lstnew(cat_list(to_cat)));
	ft_lstclear(&to_cat, ft_safe_free);
	return (tokens);
}

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

