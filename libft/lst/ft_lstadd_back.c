/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 20:22:27 by tmatis            #+#    #+#             */
/*   Updated: 2021/04/26 20:57:44 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*temp;

	if (!*alst)
	{
		*alst = new;
		return ;
	}
	temp = *alst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	ft_lstcat(t_list **dst, t_list *src)
{
	while (src)
	{
		ft_lstadd_back(dst, ft_lstnew(src->content));
		src = src->next;
	}
}

void	ft_lstremove_last(t_list **alst, void (*del)(void*))
{
	t_list	*prev;
	t_list	*lst;

	if (!*alst)
		return ;
	if (ft_lstsize(*alst) < 2)
	{
		ft_lstdelone(*alst, del);
		*alst = NULL;
		return ;
	}
	prev = *alst;
	lst = (*alst)->next;
	while (lst->next)
	{
		prev = lst;
		lst = lst->next;
	}
	prev->next = NULL;
	ft_lstdelone(lst, del);
}

void	ft_nofree(void *mem)
{
	(void)mem;
}
