/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 14:12:28 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/04 14:32:35 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H

# define EXEC_H

#include "../minishell.h"

void	exec_pipes(t_list *pipes_list, t_list *env_vars);

#endif
