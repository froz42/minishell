/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 12:02:21 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/28 22:17:39 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_manager.h"

/*
** Add a element in a chained list
*/

void	push_history(char *command, t_list **history)
{
	t_list	*elem;

	if (!command)
	{
		ft_log_error(strerror(errno));
		return ;
	}
	elem = ft_lstnew((void *)command);
	if (!elem)
	{
		free(command);
		ft_log_error(strerror(errno));
		return ;
	}
	ft_lstadd_front(history, elem);
}

/*
** search an element of index i in a chained list
*/

char	*fetch_history(int i, t_list *history)
{
	if (!history)
		return (NULL);
	while (history->next && i > 0)
	{
		history = history->next;
		i--;
	}
	return (history->content);
}
