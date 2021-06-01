/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 11:40:31 by tmatis            #+#    #+#             */
/*   Updated: 2021/06/01 11:02:10 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H

# define BUILTIN_H

# include "../minishell.h"

# define IN_PIPES		0
# define NOT_IN_PIPES	2

int		ft_cd(int argc, char **argv, t_list **env_var);
int		ft_exit(int argc, char **argv, t_list **env_var, t_bool in_pipes);
int		ft_echo(int argc, char **argv);
int		ft_env(t_list *env_var);
int		ft_unset(int argc, char **argv, t_list **env_var);
int		ft_pwd(void);
int		print_export(t_list *env_var);
char	*catch_key(char **str, int *error, int *append);
int		ft_export(int argc, char **argv, t_list **env_var);

#endif
