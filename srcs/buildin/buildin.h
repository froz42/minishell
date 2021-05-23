/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 11:40:31 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/23 13:52:36 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDIN_H

# define BUILDIN_H

# include "../minishell.h"

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