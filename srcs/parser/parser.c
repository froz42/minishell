/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 23:03:16 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/23 14:14:35 by tmatis           ###   ########.fr       */
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
	if (*str == ESC)
		return (is_special(str + 1));
	else
		return (0);
}

void	set_status_env(t_list **env_var, int status)
{
	char	*status_str;

	status_str = ft_itoa(status);
	if (!status_str)
	{
		ft_putstr_fd("Minishell: cannot set status\n", STDERR_FILENO);
		return ;
	}
	edit_var(env_var, "?", status_str);
	free(status_str);
}

/*
** Geres les char "; | >> > <" : met un \33 (escape) devant
** pour les differencier de l'user input
*/

char	*special(char **str)
{
	char	*token;

	token = ft_calloc(4, sizeof (char));
	if (!token)
		return (NULL);
	token[0] = ESC;
	if (is_special(*str) == APPEND)
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
