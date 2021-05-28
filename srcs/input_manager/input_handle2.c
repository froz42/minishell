/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handle2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 11:13:21 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/28 13:28:07 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_manager.h"

void	handle_move_on_line(t_buffer *buffer)
{
	if (buffer->escape_id == LINE_START_ID)
	{
		while (buffer->pos_before_endl < buffer->size)
			handle_left_key(buffer);
		return ;
	}
	while (buffer->pos_before_endl > 0)
		handle_right_key(buffer);
}

/*
** This is called when user type ctrl-c
*/

void	handle_ctrl_c(t_buffer *buffer)
{
	char	*dst;

	dst = ft_calloc(1, sizeof(char));
	if (!dst)
		return (eot_error(buffer));
	free(buffer->buff);
	buffer->buff = dst;
	buffer->size = 0;
	buffer->pos_before_endl = 0;
	ft_putstr("^C\n");
	print_prompt(buffer->status);
}

/*
** This is called when user type ctrl-d
*/

int	handle_ctrl_d(t_buffer *buffer)
{
	ft_safe_free(buffer->buff);
	ft_putstr_fd("\n", STDOUT_FILENO);
	buffer->buff = NULL;
	buffer->size = 0;
	buffer->pos_before_endl = 0;
	buffer->error = true;
	return (EOT);
}

/*
** This is called when user type delete
*/

void	erase_char(t_buffer *buffer)
{
	int		i;

	if (buffer->size <= buffer->pos_before_endl)
		return ;
	i = 0;
	while (i++ < buffer->pos_before_endl)
		ft_putstr(CURSOR_RIGHT);
	erase_x_chars(buffer->pos_before_endl + 1);
	ft_putstr(buffer->buff + (buffer->size - buffer->pos_before_endl));
	i = 0;
	while (i++ < buffer->pos_before_endl)
		ft_putstr(CURSOR_LEFT);
	buffer_delete(buffer->size - buffer->pos_before_endl, buffer);
}
