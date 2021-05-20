/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 14:12:28 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/20 22:21:51 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H

# define EXEC_H

#include "../minishell.h"

int	exec_pipes(t_list *pipes_list, t_list **env_vars);
int	exec(t_list *pipes_list, t_list **env_var);
void execution_error_write(char *cmd, char *error);
int				redirect_fd(t_command command, int backup[2]);
void	file_error(char *file, char *error);
void 	restore_in_out(int backup[2]);

#endif
