/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 13:17:36 by tmatis            #+#    #+#             */
/*   Updated: 2021/04/05 21:25:50 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_MANAGER_H

# define INPUT_MANAGER_H

#include "../minishell.h"

void		buffer_add(char c, t_buffer *buffer);
void		buffer_add_chain(char *src, int size, t_buffer *buffer);
void		buffer_delete(int pos, t_buffer *buffer);
t_buffer	init_buffer(void);
void		push_history(char *command, t_list **history);
char		*fetch_history(int i, t_list *history);
void		raw_mode(void);
void		buff_mode(void);
void		erase_x_chars(int x);
int			get_escape_id(char *buff, int size);
char		*get_input_line(t_list **history);
#endif
