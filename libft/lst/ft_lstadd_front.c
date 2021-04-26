/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 20:07:50 by tmatis            #+#    #+#             */
/*   Updated: 2021/04/26 18:27:33 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	new->next = *alst;
	*alst = new;
}

void	ft_lstremove_first(t_list **alst, void (*del)(void*))
{
	t_list	*temp;

	temp = (*alst)->next;
	ft_lstdelone(*alst, del);
	*alst = temp;
}
