/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handle2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 11:13:21 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/15 23:32:21 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_manager.h"

/*
** This is called when user type ctrl-c
*/

void	handle_ctrl_c(t_buffer *buffer)
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
	print_prompt(buffer->status);
}

/*
** This is called when user type ctrl-d
*/

void	handle_ctrl_d(t_buffer *buffer)
{
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

	if (buffer->size <= buffer->position)	// rename buffer->position ?
		return ;
	i = 0;
	while (i++ < buffer->position)
		ft_putstr(CUR_RIGHT);
	erase_x_chars(buffer->position + 1);
	ft_putstr(buffer->buff + (buffer->size - buffer->position));
	i = 0;
	while (i++ < buffer->position)
		ft_putstr(CUR_LEFT);
	buffer_delete(buffer->size - buffer->position, buffer);
}
