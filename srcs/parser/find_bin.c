/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 14:28:13 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/23 14:30:34 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <sys/stat.h>

/*
** return true if file exist
*/

static t_bool	file_exist(char *path)
{
	struct stat	buffer;
	int			exist;

	exist = stat(path, &buffer);
	if (exist == 0)
		return (true);
	else
		return (false);
}

static t_bool	search_path(char **paths, t_command *command)
{
	int		i;
	char	*to_check;

	i = 0;
	while (paths[i])
	{
		to_check = ft_calloc(ft_strlen(paths[i])
				+ ft_strlen(command->name) + 2, sizeof(char));
		if (!to_check)
			return (false);
		ft_strcat(to_check, paths[i]);
		ft_strcat(to_check, "/");
		ft_strcat(to_check, command->name);
		if (file_exist(to_check))
		{
			command->cmd = to_check;
			return (true);
		}
		free(to_check);
		i++;
	}
	return (true);
}

t_bool	find_bin(t_command *command, t_list *env_var)
{
	char	**paths;

	if (ft_strchr(command->name, '/'))
	{
		command->cmd = ft_strdup(command->name);
		return (command->cmd != NULL);
	}
	paths = ft_split(search_var(env_var, "PATH"), ':');
	if (!paths && search_var(env_var, "PATH") != NULL)
		return (false);
	if (!paths || !*paths)
	{
		command->cmd = ft_strdup(command->name);
		free_table(&paths);
		return (command->cmd != NULL);
	}
	if (!search_path(paths, command))
	{
		free_table(&paths);
		return (false);
	}
	free_table(&paths);
	return (true);
}
