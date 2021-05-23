/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 12:25:11 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/23 14:04:26 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_MALLOC_H

# define MY_MALLOC_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <execinfo.h>
# ifndef FAIL
#  define FAIL 1
# endif

extern void	*__libc_malloc(size_t size);

#endif