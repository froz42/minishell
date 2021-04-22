/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 11:39:08 by tmatis            #+#    #+#             */
/*   Updated: 2021/04/22 15:32:04 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H

# define PARSER_H

# include "../minishell.h"

t_list	*parse_line(char *str);
int		is_special(char *str);
t_command	*get_command(t_list **word_list);
void		free_command(void *mem);
char	*special(char **str);
t_list	*to_word(char *str, int *error);
int		escape_control(char *str);
void	free_command_list(void *mem);
#endif
