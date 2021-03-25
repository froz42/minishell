/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 18:18:17 by tmatis            #+#    #+#             */
/*   Updated: 2021/02/13 18:31:07 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assert.h"

void			ft_assert(int actual, char *behavior, t_tests *tests)
{
	if (actual && ++tests->tests_success && tests->log_level >= 3)
		printf("\033[1;32m [OK] ");
	else if (!actual && ++tests->tests_failed && tests->log_level >= 1)
		printf("\033[1;31m [KO] ");
	printf("\033[0m");
	if (behavior && (tests->log_level >= 3
			|| (!actual && tests->log_level >= 1)))
	{
		printf("%s", behavior);
		printf("\n\n");
	}
}

void			ft_assert_cmp(
		int actual, int expected, char *behavior, t_tests *tests)
{
	if (actual == expected && ++tests->tests_success && tests->log_level >= 3)
		printf("\033[1;32m [OK] ");
	else if (actual != expected && ++tests->tests_failed
			&& tests->log_level >= 1)
		printf("\033[1;31m [KO] ");
	if ((tests->log_level >= 4) || (tests->log_level >= 2
				&& actual != expected))
	{
		printf("\033[0;33m\033[3mactual: \033[4m");
		printf("%i", actual);
		printf("\033[0m\033[0;33m\033[3m, expected: \033[4m");
		printf("%i", expected);
		printf("\033[0m\n      ");
	}
	if (behavior && (tests->log_level >= 3 || ((actual != expected)
				&& tests->log_level >= 1)))
	{
		printf("\033[0m");
		printf("%s", behavior);
		printf("\n\033[0m\n");
	}
}

static	void	ft_putstrun(char *str, int pos)
{
	while (*str)
	{
		if (!pos--)
		{
			printf("\033[0;31m\033[4m");
			printf("%c", *str++);
			printf("\033[0m\033[0;33m\033[3m");
		}
		else
			printf("%c", *str++);
	}
}

static	void	ft_putdiff(char *actual, char *expected, int indexdiff)
{
	printf("\033[0;33m\033[3m\"");
	ft_putstrun(actual, indexdiff);
	printf("\" != \"");
	ft_putstrun(expected, indexdiff);
	printf("\"\033[0m\n       ");
}

void			ft_assert_strcmp(
		char *act, char *exp, char *behavior, t_tests *tests)
{
	size_t	i;

	i = 0;
	while (act[i] && act[i] == exp[i])
		i++;
	if (act[i] == exp[i] && ++tests->tests_success && tests->log_level >= 3)
		printf("\033[1;32m [OK] \033[0m");
	else if (act[i] != exp[i] && ++tests->tests_failed && tests->log_level >= 1)
		printf("\033[1;31m [KO] \033[0m");
	if (act[i] == exp[i] && tests->log_level >= 4)
	{
		printf("\033[0;33m\033[3m\"");
		printf("%s", act);
		printf("\" == \"");
		printf("%s", exp);
		printf("\"\033[0m\n       ");
	}
	else if (act[i] != exp[i] && tests->log_level >= 2)
		ft_putdiff(act, exp, i);
	if (behavior && (tests->log_level >= 3 || ((act[i] != exp[i])
				&& tests->log_level >= 1)))
	{
		printf("%s", behavior);
		printf("\n\033[0m\n");
	}
}
