/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:15:16 by jmazoyer          #+#    #+#             */
/*   Updated: 2021/05/20 23:50:34 by tmatis           ###   ########.fr       */
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
		*line = ft_strnjoin_del(*line, &(file->buffer[file->i]), len, 1);
		if (!(line))
			return (-1);
		file->i += (len + 1);
		file->stored -= (len + 1);
		if (file->stored == 0)
			file->i = 0;
		return (1);
	}
	*line = ft_strjoin_del(*line, &(file->buffer[file->i]), 1);
	if (!(*line))
		return (-1);
	file->i = 0;
	file->stored = 0;
	return (0);
}

int	compute(int fd, t_file_buff *file, char **line, int *result)
{
	file->stored = read(fd, file->buffer, BUFFER_SIZE);
	while (file->stored > 0)
	{
		file->buffer[file->stored] = '\0';
		if (file->stored < BUFFER_SIZE)
		{
			*result = build_line(file, line);
			return (1);
		}
		*result = build_line(file, line);
		if (*result)
			return (1);
		file->stored = read(fd, file->buffer, BUFFER_SIZE);
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static t_file_buff	file;
	int					result;

	if (line != NULL)
		*line = NULL;
	if (BUFFER_SIZE <= 0 || fd < 0 || line == NULL)
		return (-1);
	if (file.stored > 0)
	{
		result = build_line(&file, line);
		if (result)
			return (result);
	}
	if (compute(fd, &file, line, &result))
		return (result);
	if (file.stored == 0 && *line == NULL)
	{
		*line = (char *)ft_calloc(1, sizeof(char));
		if (*line == NULL)
			return (-1);
	}
	return (file.stored);
}
