/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 23:03:16 by tmatis            #+#    #+#             */
/*   Updated: 2021/04/10 23:37:12 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		id_redir(char **str)
{
	int	len;

	len = ft_strlen(*str);

	if (len >= 2 && !ft_memcmp(str, ">>", 2))
	{
		(*str) += 2;
		return (2);
	}
	if (**str == '<')
	{
		(*str) += 1;
		return (0);
	}
	if (**str == '>')
	{
		(*str) += 1;
		return (1);
	}
	return (-1);
}

void	parse_line(char *str)
{
	printf("%s\n", str);
	return ;
	int		id;

	if (ft_strlen(str) > 0)
	{
		while (*str)
		{
			id= id_redir(&str);
			if (id != -1)
			{
				ft_log_info("Redirection found");
				printf("redir: %i\n", id);
			}
			else
				str++;
		}
	}
	else
		ft_log_info("Empty command");
}
