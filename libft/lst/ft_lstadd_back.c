/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 20:22:27 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/17 23:29:02 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"

int	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*temp;

	if (!new)
		return (0);
	if (!*alst)
	{
		*alst = new;
		return (1);
	}
	temp = *alst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	return (1);
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
