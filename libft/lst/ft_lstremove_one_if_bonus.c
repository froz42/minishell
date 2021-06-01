/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove_one_if_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmazoyer <jmazoyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 14:46:05 by jmazoyer          #+#    #+#             */
/*   Updated: 2021/05/29 22:17:00 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"

void	ft_lstremove_one_if(t_list **alst, void *data_ref,
									int (*cmp)(), void (*free_fct)(void *))
{
	t_list	*current;
	t_list	*tmp_prev;

	current = *alst;
	tmp_prev = NULL;
	while (current != NULL)
	{
		if ((*cmp)(current->content, data_ref) == 0)
		{
			if (free_fct != NULL)
				(*free_fct)(current->content);
			if (tmp_prev == NULL)
				*alst = current->next;
			else
				tmp_prev->next = current->next;
			free(current);
			return ;
		}
		tmp_prev = current;
		current = current->next;
	}
}
