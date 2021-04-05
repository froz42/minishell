/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 18:56:01 by tmatis            #+#    #+#             */
/*   Updated: 2021/04/03 13:21:58 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

typedef struct	s_buffer
{
	int		size;
	char	*buff;
}				t_buffer;

# include "../libft/libft.h"
# include <errno.h>
# include "input_manager/input_manager.h"

#endif
