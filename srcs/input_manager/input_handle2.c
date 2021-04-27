/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handle2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 11:13:21 by tmatis            #+#    #+#             */
/*   Updated: 2021/04/27 16:13:42 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_manager.h"

/*
** This is called when user type ctrl-c
*/

void	handle_ctrlc(t_buffer *buffer)
{
	char	*dst;

	dst = calloc(1, sizeof(char));
	if (!dst)
	{
		ft_log_error(strerror(errno));
		return ;
	}
	free(buffer->buff);
	buffer->buff = dst;
	buffer->size = 0;
	buffer->position = 0;
	ft_putstr("^C\n");
	ft_putstr("Minishell $>");
}

/*
** This is called when user type ctrl-d
*/

void	handle_ctrld(t_buffer *buffer)
{
	ft_putstr("\nexit\n");
	free(buffer->buff);
	buffer->buff = ft_strdup("");
	buffer->size = ft_strlen(buffer->buff);
	buffer->position = 0;
}

/*
** This is called when user type delete
*/

void	erase_char(t_buffer *buffer)
{
	int		i;

	if (buffer->size <= buffer->position)
		return ;
	i = 0;
	while (i++ < buffer->position)
		ft_putstr("\033[1C");
	erase_x_chars(buffer->position + 1);
	ft_putstr(buffer->buff + (buffer->size - buffer->position));
	i = 0;
	while (i++ < buffer->position)
		ft_putstr("\033[1D");
	buffer_delete(buffer->size - buffer->position, buffer);
}
