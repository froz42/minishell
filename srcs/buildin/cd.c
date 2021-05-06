/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 21:07:44 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/06 20:34:02 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	generic_error(char *error, char *path)
{
	ft_putstr_fd("Minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
}

int		ft_cd(int argc, char **argv, t_list **env_var)
{
	char	actual_dir[BUFFER_SIZE];
	int		ret;
	(void)env_var;
	(void)argv;
	(void)argc;

	getcwd(actual_dir, sizeof(actual_dir));
	edit_var(env_var, "OLDPWD", actual_dir);
	if (argc == 2)
	{
		ret = chdir(argv[1]);
		if (ret == -1)
		{
			generic_error(strerror(errno), argv[1]);
			return (1);
		}
		getcwd(actual_dir, sizeof(actual_dir));
		edit_var(env_var, "PWD", actual_dir);
	}
	else if (argc > 2)
	{
		ft_putstr_fd("Minishell: cd: too mutch arguments\n", 2);
		return (1);
	}
	return (0);
}