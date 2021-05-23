/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 12:24:09 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/23 14:03:53 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_malloc.h"
#include <errno.h>

int	g_malloc_hook_active = 1;

void	*my_malloc_hook(size_t size, void *caller)
{
	void		*result;
	static int	fail_counter = 0;

	(void)caller;
	g_malloc_hook_active = 0;
	if (++fail_counter == FAIL)
	{
		errno = ENOMEM;
		fail_counter = 0;
		result = NULL;
	}
	else
		result = malloc(size);
	g_malloc_hook_active = 1;
	return (result);
}

void	*malloc(size_t size)
{
	void	*caller;

	caller = __builtin_return_address(0);
	if (g_malloc_hook_active)
		return (my_malloc_hook(size, caller));
	return (__libc_malloc(size));
}
