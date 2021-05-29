/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 21:07:44 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/29 20:48:52 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	generic_error(char *error, char *path)
{
	ft_putstr_fd("Minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	return (1);
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
	else if (chdir(home) == -1)
		return (generic_error(strerror(errno), "HOME"));
	return (0);
}

static t_bool	get_directories(char **old_pwd, char *actual_dir,
										t_list **env_var, char *var_to_edit)
{
	if (old_pwd)
	{
		*old_pwd = ft_strdup(*old_pwd);
		if (!*old_pwd)
		{
			file_error("cannot load OLDPWD", strerror(errno));
			return (false);
		}
	}
	if (!getcwd(actual_dir, BUFFER_SIZE))
	{
		file_error("cannot get PWD", strerror(errno));
		if (old_pwd)
			free(*old_pwd);
		return (false);
	}
	if (!edit_var(env_var, var_to_edit, actual_dir))
	{
		if (old_pwd)
			free(*old_pwd);
		return (false);
	}
	return (true);
}

static int	cd_oldpwd(t_list **env_var)
{
	char	*old_pwd;
	char	actual_dir[BUFFER_SIZE];

	old_pwd = search_var(*env_var, "OLDPWD");
	if (!old_pwd)
	{
		ft_putstr_fd("Minishell: cd: OLDPWD not set\n", 2);
		return (1);
	}
	if (!get_directories(&old_pwd, actual_dir, env_var, "OLDPWD"))
		return (1);
	if (chdir(old_pwd) == -1)
	{
		generic_error(strerror(errno), old_pwd);
		free(old_pwd);
		return (1);
	}
	ft_putnl(old_pwd);
	free(old_pwd);
	if (!get_directories(NULL, actual_dir, env_var, "PWD"))
		return (1);
	return (0);
}

int	ft_cd(int argc, char **argv, t_list **env_var)
{
	char	actual_dir[BUFFER_SIZE];

	if (argc == 2)
	{
		if (!ft_strcmp(argv[1], "-"))
			return (cd_oldpwd(env_var));
		if (!get_directories(NULL, actual_dir, env_var, "OLDPWD"))
			return (1);
		if (chdir(argv[1]) == -1)
			return (generic_error(strerror(errno), argv[1]));
		if (!get_directories(NULL, actual_dir, env_var, "PWD"))
			return (1);
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
