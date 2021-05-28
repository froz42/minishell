/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 13:17:36 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/28 13:23:06 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_MANAGER_H

# define INPUT_MANAGER_H

# include "../minishell.h"

# define DEL				127
# define BS					8
# define DEL_ID				0
# define UP_KEY				"\33\133\101"
# define UP_KEY_ID			1
# define DOWN_KEY			"\33\133\102"
# define DOWN_KEY_ID		2
# define RIGHT_KEY			"\33\133\103"
# define RIGHT_KEY_ID		3
# define LEFT_KEY			"\33\133\104"
# define LEFT_KEY_ID		4
# define LF					10
# define LF_ID				5
# define ETX				3
# define ETX_ID				6
# define EOT				4
# define EOT_ID				7
# define FF					12
# define CLR_SCREEN_ID		8
# define WORD_RIGHT			"\33\133\61\73\65\103"
# define WORD_RIGHT_ID		9
# define WORD_LEFT			"\33\133\61\73\65\104"
# define WORD_LEFT_ID		10
# define LINE_START			1
# define HOME_KEY			"\33\133\110"
# define LINE_START_ID		11
# define LINE_END			5
# define END_KEY			"\33\133\106"
# define LINE_END_ID		12
# define CUT_WORD_RIGHT		"\33\144"
# define CUT_WORD_RIGHT_ID	13
# define CUT_WORD_LEFT		23
# define CUT_WORD_LEFT_ID	14
# define CUT_LINE_START		21
# define CUT_LINE_START_ID	15
# define CUT_LINE_END		11
# define CUT_LINE_END_ID	16
# define PASTE				25
# define PASTE_ID			17
# define SUPPR_KEY			"\33\133\63\176"
# define SUPPR_ID			18

# define CURSOR_RIGHT		"\033[1C"
# define CURSOR_LEFT		"\033[1D"

# define CLEAR_SCREEN		"\033[2J\033[H"

void			buffer_add(char c, t_buffer *buffer);
void			buffer_add_chain(char *src, int size, t_buffer *buffer);
void			buffer_delete(int pos, t_buffer *buffer);
t_buffer		init_buffer(char *clipboard, char *status);
void			push_history(char *command, t_list **history);
char			*fetch_history(int i, t_list *history);
struct termios	raw_mode(void);
void			buff_mode(struct termios old);
void			erase_x_chars(int x);
int				get_escape_id(char *buff, int size);
void			display_escape_code(char *buff, int size);
int				get_input_line(char **line, char **clipboard,
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
void			eot_error(t_buffer *buffer);
void			handle_eot_error(t_buffer *buffer);
void			handle_cut_word_right(t_buffer *buffer);
void			handle_cut_word_left(t_buffer *buffer);
void			handle_move_word_right(t_buffer *buffer);
void			handle_move_word_left(t_buffer *buffer);
void			handle_cut_line(t_buffer *buffer);
void			handle_move_on_line(t_buffer *buffer);

#endif
