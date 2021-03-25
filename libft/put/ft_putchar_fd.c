/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 11:56:01 by tmatis            #+#    #+#             */
/*   Updated: 2021/01/04 16:35:46 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"
#include "../char/char.h"
#include <unistd.h>

void	ft_putchar_fd(int c, int fd)
{
	char	buff[4];
	int		len;

	len = ft_utf8_encode(c, buff);
	write(fd, buff, len);
}
