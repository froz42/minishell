/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 12:19:08 by tmatis            #+#    #+#             */
/*   Updated: 2021/04/27 15:50:01 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSERT_H

# define ASSERT_H

# include <stdio.h>
# include <string.h>

typedef struct s_tests
{
	int		tests_success;
	int		tests_failed;
	int		log_level;
	char	name[256];
}				t_tests;

t_tests			init_tester(char name[256], int log_level);
void			tests_header(t_tests *tests);
void			tests_result(t_tests *tests);
void			ft_assert(int actual, char *behavior, t_tests *tests);
void			ft_assert_cmp(int act, int exp, char *behavior, t_tests *tests);
void			ft_assert_strcmp(char *act, char *exp, char *behavior,
					t_tests *tests);
#endif
