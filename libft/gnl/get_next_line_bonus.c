/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmazoyer <jmazoyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:15:16 by jmazoyer          #+#    #+#             */
/*   Updated: 2021/05/17 14:51:47 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../libft.h"

static int	build_line(t_file_buff *file, char **line)
{
	char	*newline;
	int		len;

	newline = ft_strchr(&(file->buffer[file->i]), '\n');
	if (newline != NULL)
	{
		len = newline - &(file->buffer[file->i]);
		if (!(*line = ft_strnjoin_del(*line, &(file->buffer[file->i]), len, 1)))
			return (-1);
		file->i += (len + 1);
		file->stored -= (len + 1);
		if (file->stored == 0)
			file->i = 0;
		return (1);
	}
	if (!(*line = ft_strjoin_del(*line, &(file->buffer[file->i]), 1)))
		return (-1);
	file->i = 0;
	file->stored = 0;
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static t_file_buff	file;
	int					result;

	if (line != NULL)
		*line = NULL;
	if (BUFFER_SIZE <= 0 || fd < 0 || line == NULL)
		return (-1);
	if (file.stored > 0 && (result = build_line(&file, line)) != 0)
		return (result);
	while ((file.stored = read(fd, file.buffer, BUFFER_SIZE)) > 0)
	{
		file.buffer[file.stored] = '\0';
		if (file.stored < BUFFER_SIZE)
			return (build_line(&file, line));
		if ((result = build_line(&file, line)) != 0)
			return (result);
	}
	if (file.stored == 0 && *line == NULL)
		if ((*line = (char *)ft_calloc(1, sizeof(char))) == NULL)
			return (-1);
	return (file.stored);
}
