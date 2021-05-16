/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 13:17:36 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/16 17:24:27 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_MANAGER_H

# define INPUT_MANAGER_H

# include "../minishell.h"

# define DEL			127
# define BS				8
# define DEL_ID			0
# define UP_KEY			"\33\133\101"
# define UP_KEY_ID		1
# define DOWN_KEY		"\33\133\102"
# define DOWN_KEY_ID	2
# define RIGHT_KEY		"\33\133\103"
# define RIGHT_KEY_ID	3
# define LEFT_KEY		"\33\133\104"
# define LEFT_KEY_ID	4
# define LF				10
# define LF_ID			5
# define ETX			3
# define ETX_ID			6
# define EOT			4
# define EOT_ID			7
# define FF				12
# define CLR_SCREEN_ID	8

# define CURSOR_RIGHT	"\033[1C"
# define CURSOR_LEFT	"\033[1D"

# define CLEAR_SCREEN	"\033[2J\033[H"

void			buffer_add(char c, t_buffer *buffer);
void			buffer_add_chain(char *src, int size, t_buffer *buffer);
void			buffer_delete(int pos, t_buffer *buffer);
t_buffer		init_buffer(t_bool manage_history, char *status);
void			push_history(char *command, t_list **history);
char			*fetch_history(int i, t_list *history);
struct termios	raw_mode(void);
void			buff_mode(struct termios old);
void			erase_x_chars(int x);
int				get_escape_id(char *buff, int size);
void			display_escape_code(char *buff, int size);
int				get_input_line(char **line, t_bool manage_history,
					t_list **history, char *status);
void			erase_char(t_buffer *buffer);
void			handle_down_key(t_buffer *buffer, int *history_fetch,
					char **temp, t_list *history);
void			handle_up_key(t_buffer *buffer, int *history_fetch,
					char **temp, t_list *history);
void			handle_ctrl_c(t_buffer *buffer);
int				handle_ctrl_d(t_buffer *buffer);
void			handle_left_key(t_buffer *buffer);
void			handle_right_key(t_buffer *buffer);
void			print_prompt(char *status);
void			handle_ctrl_l(t_buffer *buffer);

#endif
