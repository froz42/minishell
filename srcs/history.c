/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 12:02:21 by tmatis            #+#    #+#             */
/*   Updated: 2021/03/31 13:59:42 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Add a element in a chained list 
*/

void	push_history(char *command, t_list **history)
{
	t_list	*new;

	new = ft_lstnew((void *)command);
	if (!new)
	{
		ft_log_error(strerror(errno));
		return ;
	}
	ft_lstadd_front(history, new);
}
