/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 14:54:03 by tmatis            #+#    #+#             */
/*   Updated: 2021/01/13 13:19:43 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG_H

# define LOG_H
# include "../libft.h"

void	ft_log_warn(char *log);
void	ft_log_info(char *log);
void	ft_log_error(char *log);
void	ft_log_task(char *log);
void	ft_log_ok(t_bool b);

#endif
