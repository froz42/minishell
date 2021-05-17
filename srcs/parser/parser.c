/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 23:03:16 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/17 21:54:42 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Retourne la valeur associee a un caractere special et 0 sinon
*/

int	is_special(char *str)
{
	int		strlen;

	strlen = ft_strlen(str);
	if (strlen >= 2 && !ft_memcmp(str, ">>", 2))
		return (APPEND);
	if (*str == '>')
		return (REDIR_OUT);
	if (*str == '<')
		return (REDIR_IN);
	if (*str == '|')
		return (PIPE);
	if (*str == ';')
		return (SEMICOLON);
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

//	token_list = tokenize(str, error, env_var, true);
	token_list = tokenize(str, error, env_var);
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
	t_list		*pipe_list;
	int			error;
	int			return_value;

	error = NO_ERROR;
	word_list = tokenize_all(str, &error, *env_var);
//	word_list = tokenize(str, &error, *env_var); // passer direct juste le ptr ?
	if (error != NO_ERROR)
		write_error(error);
	else
	{
		error_detector(word_list, &error);
		ft_lstclear(&word_list, free);
		if (error != NO_ERROR)
			write_error(error);
		else
		{
			while (*str)
			{
				pipe_list = get_next_pipes(&str, &error, *env_var);
				return_value = exec(pipe_list, env_var);
				ft_lstclear(&pipe_list, free_command);
				if (return_value)
					return (return_value);
			}
		}
	}
	return (0);
//	return (0 + (error != NO_ERROR)); // exit si erreur ?
}
