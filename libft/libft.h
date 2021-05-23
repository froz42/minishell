/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 16:43:44 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/23 13:57:01 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H

# include "typedef.h"
# include "assert/assert.h"
# include "char/char.h"
# include "lst/lst.h"
# include "memory/memory.h"
# include "misc/misc.h"
# include "string/string.h"
# include "wstring/wstring.h"
# include "put/put.h"
# include "gnl/ft_gnl.h"
# include "log/log.h"
# include "maths/maths.h"

typedef struct s_file_buff
{
	char				buffer[BUFFER_SIZE + 1];
	size_t				i;
	int					stored;
}				t_file_buff;

int			get_next_line(int fd, char **line);
size_t		ft_min_size_t(size_t a, size_t b);
char		*ft_strjoin_del(char *s1, char *s2, int to_del);
char		*ft_strnjoin_del(char *s1, char *s2, size_t n, int to_del);

#endif
