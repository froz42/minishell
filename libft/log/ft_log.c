/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 14:04:16 by tmatis            #+#    #+#             */
/*   Updated: 2021/03/29 12:28:50 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.h"

void	ft_log_info(char *log)
{
	printf("[\033[0;32mINFO\x1b[0m] %s\n", log);
}

void	ft_log_error(char *log)
{
	printf("[\033[0;31mERROR\x1b[0m] %s\n", log);
}

void	ft_log_warn(char *log)
{
	printf("[\033[0;33mWARN\x1b[0m] %s\n", log);
}

void	ft_log_task(char *log)
{
	printf("[\033[0;34mTASK\x1b[0m] %s", log);
}

void	ft_log_ok(t_bool b)
{
	if (b)
		printf("\033[0;32m[OK]\x1b[0m\n");
	else
		printf("\033[0;31m[KO]\x1b[0m\n");
}
