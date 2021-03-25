/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:42:42 by tmatis            #+#    #+#             */
/*   Updated: 2021/02/03 21:56:52 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GNL_H

# define FT_GNL_H
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# define BUFFER_SIZE 2048

typedef	struct	s_chunk
{
	char	*data;
	int		len;
	int		init;
}				t_chunk;

t_chunk			*ft_rallocat(t_chunk *chunk, char *data, int len);
t_chunk			*ft_rallocut(t_chunk *chunk, int start);
char			*ft_extractstr(t_chunk *chunk, int size);
void			ft_initchunk(t_chunk *chunk);
int				ft_getendl(t_chunk *chunk);
int				ft_gnl(int fd, char **line);
#endif
