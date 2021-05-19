/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_detector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 17:03:04 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/19 18:29:14 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	return_seterror(int n, int *error)
{
	*error = n;
	return (1);
}

int	get_errno(int special_id)
{
	return (special_id + 2);
}

int	error_unexpected(t_list *tokens, int *error)
{
	int		special_id;

	special_id = escape_control(tokens->content);
	if (special_id == PIPE && !tokens->next)
		return (return_seterror(EOL_ERR, error));
	if ((special_id == REDIR_OUT || special_id == REDIR_IN || special_id == APPEND)
		&& tokens->next && escape_control(tokens->next->content))
		return (return_seterror(
				get_errno(escape_control(tokens->next->content)), error));
	if ((special_id == REDIR_OUT || special_id == REDIR_IN || special_id == APPEND)
		&& !tokens->next)
			return (return_seterror(NL_ERR, error));
	if ((special_id == PIPE || special_id == SEMICOLON) && tokens->next
		&& (escape_control(tokens->next->content) == PIPE
			|| escape_control(tokens->next->content) == SEMICOLON))
		return (return_seterror(
				get_errno(escape_control(tokens->next->content)), error));
	return (0);
}

void	error_detector(t_list *tokens, int *error)
{
	if (tokens && escape_control(tokens->content) == SEMICOLON) // what for ?
//	{
//		printf("!\n");
//		*error = get_errno(SEMICOLON);
//	}
		return_seterror(get_errno(escape_control(tokens->content)), error);
//	return ;
	while (tokens)
	{
		if (error_unexpected(tokens, error))
			return ;
		tokens = tokens->next;
	}
}
