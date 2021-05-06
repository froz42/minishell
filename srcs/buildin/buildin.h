/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 11:40:31 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/06 11:42:24 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDIN_H

# define BUILDIN_H

#include "../minishell.h"

int		ft_cd(int argc, char **argv, t_list **env_var);
int		ft_exit(int argc, char **argv);

#endif