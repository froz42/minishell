/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 15:28:01 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/21 22:37:17 by jmazoyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <sys/stat.h>

/*
** Init the command structure
*/

static t_command	*init_command(void)
{
	t_command	*command;

	command = calloc(1, sizeof(t_command));
	if (!command)
		return (NULL);
	command->is_set = false;
	return (command);
}

/*
** Parse a potential redirection, iter on word_list
*/

static t_redir	*get_redir(t_list **word_list, int special_id)
{
	t_redir		*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = special_id;
	redir->file = NULL;
	*word_list = (*word_list)->next;
	if (*word_list)
	{
		special_id = escape_control((*word_list)->content);
		if (special_id != SEMICOLON && special_id != PIPE)
		{
			redir->file = ft_strdup((*word_list)->content);
			if (!redir->file)
			{
				free(redir);
				return (NULL);
			}
			*word_list = (*word_list)->next;
		}
	}
	return (redir);
}

/*
** return true if file exist
*/

t_bool	file_exist(char *path)
{
	struct stat	buffer;
    int			exist;

	exist = stat(path, &buffer);
    if (exist == 0)
		return (true);
    else
		return (false);
}

/*
** Set the command in the struct
*/

void	free_table(char ***table)
{
	int		i;

	i = 0;
	if (!*table)
		return ;
	while ((*table)[i])
		free((*table)[i++]);
	free(*table);
}
/*
char	*find_bin(char *bin, t_list *env_var)
{
	char	**paths;
	int		i;
	char	*to_check;

	if (ft_strchr(bin, '/'))
		return (ft_strdup(bin));
	paths = ft_split(search_var(env_var, "PATH"), ':');
	if (!paths || !*paths)
	{
		free_table(&paths);
		return (ft_strdup(bin)); // plutot NULL ? // Et log_error ?
	}
	i = 0;
	while (paths[i])
	{
		to_check = ft_calloc(ft_strlen(paths[i]) + ft_strlen(bin) + 2, sizeof(char));
		if (!to_check)
			return (ft_strdup(bin)); // plutot NULL ? // Et log_error ?
		ft_strcat(to_check, paths[i]);
		ft_strcat(to_check, "/");
		ft_strcat(to_check, bin);
		if (file_exist(to_check))
		{
			free_table(&paths);
			return (to_check);
		}
		free(to_check);
		i++;
	}
	free_table(&paths);
	return(NULL);
}
*/
t_bool	search_path(char **paths, t_command *command)
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

static t_bool	set_command(t_list	**word_list, t_command *command, t_list *env_var)
{
	command->name = ft_strdup((*word_list)->content);
	if (!command->name || !find_bin(command, env_var))
	{
		ft_log_error(strerror(errno));
		free_command(command);
		return (false);
	}
	command->is_set = true;
	*word_list = (*word_list)->next;
	return (true);
}

/*
** Retourne l'argument et passe au suivant
*/

static char	*get_arg(t_list **word_list)
{
	char	*dst;

	dst = ft_strdup((*word_list)->content);
	*word_list = (*word_list)->next;
	return (dst);
}

/*
** retourne l'objet t_command en utilisant les tokens
** jusqu'a rencontrer un token | ou ;
** le premier token a ne pas etre une redirection est considere
** comme la commande
*/

t_command	*get_command(t_list **word_list, t_list *env_var)
{
	t_command	*command;
	int			special_id;
	t_redir		*redir;
	t_list		*elem;
	char		*arg;

	command = init_command();
	if (!command)
		return (NULL);
	while (*word_list)
	{
		special_id = escape_control((*word_list)->content);
		if (special_id == SEMICOLON || special_id == PIPE)
			break ;
		if (special_id == REDIR_OUT || special_id == REDIR_IN || special_id == APPEND)
		{
			redir = get_redir(word_list, special_id);
			if (redir)
				elem = ft_lstnew(redir);
			if (!redir || !elem)
			{
				ft_safe_free(redir);
				free_command(&command);
				return (NULL);
			}
			ft_lstadd_back(&command->redirs, elem);
		}
		else if (!command->is_set)
		{
			if (!set_command(word_list, command, env_var))
				return (NULL);
		}
		else
		{
			arg = get_arg(word_list);
			if (arg)
				elem = ft_lstnew(arg);
			if (!arg || !elem)
			{
				ft_safe_free(arg);
				free_command(&command);
				return (NULL);
			}
			ft_lstadd_back(&command->args, elem);
		}
	}
	return (command);
}
