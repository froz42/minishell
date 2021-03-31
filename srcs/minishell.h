/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 18:56:01 by tmatis            #+#    #+#             */
/*   Updated: 2021/03/31 21:00:19 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>

typedef struct	s_buffer
{
	int		size;
	char	*buff;
}				t_buffer;

void		buffer_add(char c, t_buffer *buffer);
void		buffer_delete(int pos, t_buffer *buffer);
t_buffer	init_buffer(void);
void	push_history(char *command, t_list **history);

#endif
