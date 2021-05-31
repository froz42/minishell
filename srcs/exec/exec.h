/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 14:12:28 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/31 23:58:42 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H

# define EXEC_H

# include "../minishell.h"

# define EXIT_ERROR		2
# define IS_CHILD		2

int		exec_pipes(t_list *pipes_list, t_list **env_vars);
int		exec(t_list *pipes_list, t_list **env_var);
void	execution_error_write(char *cmd, char *error);
t_bool	redirect_fd(t_command command, int backup[2]);
void	file_error(char *file, char *error);
void	restore_in_out(int backup[2]);
t_bool	redir_dup_fail(int backup[2]);
void	restore_in_out(int backup[2]);
int		get_open_flags(int type);
int		execution_rules(t_command *command, t_list **env_vars);
void	close_all_pipes(t_tube *tube_list, int size);
void	close_finish_tube(t_tube *tube_list, int forks_running, int fork_n);
void	execution_error_status(char *cmd, char *error, int status,
			t_list **env_vars);
int		handle_dup2_error(t_tube *tube_list);
void	sig_handler(int signal_no);
int		child_process(t_child_data child_data);
void	*return_and_free(char **envp, int i);
char	**build_env(t_list *env_var);
char	**build_argv(char *name, t_list *args);
int		build_argc(char **argv);
void	add_ls_color(t_command *command);

#endif
