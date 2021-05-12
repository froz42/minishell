/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 23:03:16 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/11 22:55:15 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Retourne la valeur associer a chaque caractere special et 0 si pas bon
*/

int	is_special(char *str)
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

/*
** Permet de lire une escape seq apres tokenisation
*/

int	escape_control(char *str)
{
	if (*str == '\33')
		return (is_special(str + 1));
	else
		return (0);
}

/*
** Cree une liste de commande execute simultanement relier par des pipes
*/

t_list	*pipes_commands(t_list *word_list, t_list *env_var)
{
	t_list		*pipes_list;
	int			special_id;

	pipes_list = NULL;
	while (word_list)
	{
		special_id = escape_control(word_list->content);
		if (special_id == 3)
			word_list = word_list->next;
		if (special_id == 5 || !word_list)
			break ;
		ft_lstadd_back(&pipes_list, ft_lstnew(get_command(&word_list, env_var)));
	}
	return (pipes_list);
}

t_list	*get_next_pipes(char **str, int *error, t_list *env_var)
{
	t_list	*token_list;
	t_list	*pipes_list;

	token_list = tokenize(str, error, env_var, true);
	pipes_list = pipes_commands(token_list, env_var);
	ft_lstclear(&token_list, ft_safe_free);
	return (pipes_list);
}

/*
** Fonction qui va call le tokensisateur et parse_commands et call l'exec
*/

int	exec_line(char *str, t_list **env_var)
{
	t_list		*word_list;
	t_list		*pipes_list;
	int			error;
	int			return_value;

	error = -1;
	word_list = tokenize_all(str, &error, *env_var);
	if (error != -1)
		write_error(error);
	else
	{
		error_detector(word_list, &error);
		ft_lstclear(&word_list, free);
		if (error != -1)
			write_error(error);
		else
		{
			while (*str)
			{
				pipes_list = get_next_pipes(&str, &error, *env_var);
				return_value = exec(pipes_list, env_var);
				ft_lstclear(&pipes_list, free_command);
				if (return_value)
					return (return_value);
			}
		}
	}
	return (0);
}
