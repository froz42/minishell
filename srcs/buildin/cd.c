/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 21:07:44 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/11 13:33:12 by tmatis           ###   ########.fr       */
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

static int	cd_home(t_list **env_var)
{
	char	*home;

	home = search_var(*env_var, "HOME");
	if (!home)
	{
		ft_putstr_fd("Minishell: cd: HOME not set\n", 2);
		return (1);
	}
	else
		chdir(home);
	return (0);
}

int		cd_oldpwd(t_list **env_var)
{
	char	*old_pwd;
	int		ret;
	char	actual_dir[BUFFER_SIZE];

	old_pwd = search_var(*env_var, "OLDPWD");
	if (!old_pwd)
	{
		ft_putstr_fd("Minishell: cd: OLDPWD not set\n", 2);
		return (1);
	}
	old_pwd = ft_strdup(old_pwd);
	getcwd(actual_dir, sizeof(actual_dir));
	edit_var(env_var, "OLDPWD", actual_dir);
	ret = chdir(old_pwd);
	if (ret == -1)
	{
		generic_error(strerror(errno), old_pwd);
		free(old_pwd);
		return (1);
	}
	getcwd(actual_dir, sizeof(actual_dir));
	edit_var(env_var, "PWD", actual_dir);
	free(old_pwd);
	return (0);
}

int		ft_cd(int argc, char **argv, t_list **env_var)
{
	char	actual_dir[BUFFER_SIZE];
	int		ret;

	if (argc == 2)
	{
		if (!ft_strcmp(argv[1], "-"))
			return (cd_oldpwd(env_var));
		getcwd(actual_dir, sizeof(actual_dir));
		edit_var(env_var, "OLDPWD", actual_dir);
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
		ft_putstr_fd("Minishell: cd: too many arguments\n", 2);
		return (1);
	}
	else if (argc == 1)
		return (cd_home(env_var));
	return (0);
}