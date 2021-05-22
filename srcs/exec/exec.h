/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 14:12:28 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/22 19:36:09 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H

# define EXEC_H

# include "../minishell.h"

int		exec_pipes(t_list *pipes_list, t_list **env_vars);
int		exec(t_list *pipes_list, t_list **env_var);
void	execution_error_write(char *cmd, char *error);
int		redirect_fd(t_command command, int backup[2]);
void	file_error(char *file, char *error);
void	restore_in_out(int backup[2]);
int		redir_dup_fail(char *file, int backup[2]);
void	restore_in_out(int backup[2]);
int		get_open_flags(int type);
int 	execution_rules(t_command command, t_list **env_vars);
void 	close_all_pipes(t_tube *tube_list, int size);
void 	close_finish_tube(t_tube *tube_list, int forks_running, int fork_n);
void 	execution_error_status(char *cmd, char *error, int status, t_list **env_vars);
int 	handle_dup2_error(t_tube *tube_list, int forks_running, int fork_n);
void 	sig_handler(int signal_no);
int		child_process(t_child_data child_data);


#endif
