/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 23:03:16 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/06 12:36:10 by tmatis           ###   ########.fr       */
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

t_list	*pipes_commands(t_list **word_list, t_list *env_var)
{
	t_list		*pipes_list;
	int			special_id;

	pipes_list = NULL;
	while (*word_list)
	{
		special_id = escape_control((*word_list)->content);
		if (special_id == 3)
			(*word_list) = (*word_list)->next;
		if (special_id == 5 || !*word_list)
			break ;
		ft_lstadd_back(&pipes_list, ft_lstnew(get_command(word_list, env_var)));
	}
	return (pipes_list);
}

/*
** Parse les commande a partire des tokens et genere une structure de donnee
** EX: 'cat Makefile | cat -e > test_out; < test_out wc -l'
**┌ t_list
**│ • ┌ t_list
**│   │ • ┌ t_command
**│   │   │ • cmd = "cat"
**│   │   │ • args = {"Makefile"}
**│   │   │ • redirs = {}
**│   │ • ┌ t_command
**│   │   │ • cmd = "cat"
**│   │   │ • args = {"-e"}
**│   │   │ • redirs = {{type = 1, file = test_out}}
**│ • ┌ t_list
**│   │ • ┌ t_command
**│   │   │ • cmd = "wc"
**│   │   │ • args = {"-l"}
**│   │   │ • redirs = {{type = 2, file = test_out}}
**
** Vous pouvez generer un graph dans display.c (display_commands)
*/

t_list	*parse_commands(t_list *word_list, t_list *env_var)
{
	t_list		*commands_list;

	commands_list = NULL;
	while (word_list)
	{
		if (escape_control(word_list->content) == 5)
			word_list = word_list->next;
		if (!word_list)
			break ;
		ft_lstadd_back(&commands_list, ft_lstnew(pipes_commands(&word_list, env_var)));
	}
	return (commands_list);
}

/*
** Fonction qui va call le tokensisateur et parse_commands et afficher une erreur
** TODO: Assignation
** TODO: Verification
*/

t_list	*parse_line(char *str, t_list *env_var)
{
	t_list		*word_list;
	t_list		*commands_list;
	int			error;

	commands_list = NULL;
	error = -1;
	word_list = to_word(str, &error, env_var);
	if (error != -1)
		write_error(error);
	else
	{
		error_detector(word_list, &error);
		if (error != -1)
			write_error(error);
		else
		{
			commands_list = parse_commands(word_list, env_var);
			//display_commands(commands_list);
		}
	}
	ft_lstclear(&word_list, free);
	return (commands_list);
}
