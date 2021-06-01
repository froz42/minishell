/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_detector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 17:03:04 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/31 23:39:33 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	set_error(int n, int *error)
{
	*error = n;
	return (1);
}

static int	get_errno(int special_id)
{
	return (special_id + 2);
}

static int	error_unexpected(t_list *tokens, int *error)
{
	int		special_id;
	int		special_id_next;

	special_id = escape_control(tokens->content);
	if (tokens->next)
		special_id_next = escape_control(tokens->next->content);
	if (special_id == PIPE && !tokens->next)
		return (set_error(EOL_ERR, error));
	if ((special_id == REDIR_OUT || special_id == REDIR_IN
			|| special_id == APPEND) && !tokens->next)
		return (set_error(NL_ERR, error));
	if ((special_id == REDIR_OUT || special_id == REDIR_IN
			|| special_id == APPEND) && tokens->next && special_id_next)
		return (set_error(get_errno(special_id_next), error));
	if ((special_id == PIPE || special_id == SEMICOLON) && tokens->next
		&& (special_id_next == PIPE || special_id_next == SEMICOLON))
		return (set_error(get_errno(special_id_next), error));
	return (0);
}

void	error_detector(t_list *tokens, int *error)
{
	if (*error != NO_ERROR)
		return ;
	if (tokens && escape_control(tokens->content) == SEMICOLON)
	{
		*error = get_errno(SEMICOLON);
		return ;
	}
	while (tokens)
	{
		if (error_unexpected(tokens, error))
			return ;
		tokens = tokens->next;
	}
}
