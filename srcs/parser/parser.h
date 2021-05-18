/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 11:39:08 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/18 12:27:42 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H

# define PARSER_H

# include "../minishell.h"

# define REDIR_OUT	1
# define REDIR_IN	2
# define PIPE		3
# define APPEND		4
# define SEMICOLON	5

# define LOG_ERROR	10

# define ESC		'\33'

int			is_special(char *str);
//t_list		*tokenize(char **str, int *error, t_list *env_var,
//				t_bool just_pipes);
t_list		*tokenize(char **str, int *error, t_list *env_var);
t_list		*tokenize_all(char *str, int *error, t_list *env_var);
t_command	*get_command(t_list **word_list, t_list *env_var);
void		free_command(void *mem);
char		*special(char **str);
int			exec_line(char *str, t_list **env_var);
int			escape_control(char *str);
void		free_command_list(void *mem);
void		display_commands(t_list *commands_list);
char		*make_double_quote(char **str, int *error,
				t_list *env_var);
char		*dollar(char **str, t_list *env_var);
t_list		*dollar_tokenize(char **str, t_append *append, t_list *env_var);
char		*join_list(t_list *to_cat);
char		*single_quote(char **str, int *error);
char		*backslash_double_quote(char **str);
char		*backslash(char **str);
char		*double_quote(char **str);
char		*make_double_quote(char **str, int *error, t_list *env_var);
char		*word(char **str);
t_list		*make_word(char **str, int *error, t_list *env_var);
void		error_detector(t_list *tokens, int *error);
void		free_table(char ***table);
#endif
