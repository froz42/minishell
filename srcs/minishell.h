/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 18:56:01 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/08 16:28:59 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <errno.h>
# include "../libft/libft.h"
# include "minishell_types.h"
# include "buildin/buildin.h"
# include "parser/parser.h"
# include "input_manager/input_manager.h"
# include "exec/exec.h"

void			write_error(int error_number);
t_list			*build_var(char **envp);
char			*search_var(t_list *var_list, char *key);
void			free_var(void *mem);
void			edit_var(t_list **var_list, char *key, char *value);
char			**build_env(t_list *env_var);
char			**build_argv(char *name, t_list *args);
int				build_argc(char **argv);
int				redirect_fd(t_command command, int backup[2]);

#endif
