/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_detector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 17:03:04 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/12 13:00:37 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	return_seterror(int no, int *error)
{
	*error = no;
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
	if (special_id == 3 && !tokens->next)
		return (return_seterror(2, error));
	if ((special_id == 1 || special_id == 2 || special_id == 4)
		&& tokens->next && escape_control(tokens->next->content))
		return (return_seterror(
				get_errno(escape_control(tokens->next->content)), error));
	if ((special_id == 1 || special_id == 2 || special_id == 4)
		&& !tokens->next)
			return (return_seterror(8, error));
	if ((special_id == 3 || special_id == 5) && tokens->next
		&& (escape_control(tokens->next->content) == 3
			|| escape_control(tokens->next->content) == 5))
		return (return_seterror(
				get_errno(escape_control(tokens->next->content)), error));
	return (0);
}

void	error_detector(t_list *tokens, int *error)
{
	if (tokens && escape_control(tokens->content) == 5)
		return_seterror(get_errno(escape_control(tokens->content)), error);
	while (tokens)
	{
		if (error_unexpected(tokens, error))
			return ;
		tokens = tokens->next;
	}
}
