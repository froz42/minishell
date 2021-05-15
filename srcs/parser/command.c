/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 15:28:01 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/15 14:40:33 by tmatis           ###   ########.fr       */
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
	return (command);
}

/*
** Parse a potential redirection, iter on word_list
*/

static t_redir	*get_redir(t_list **word_list)
{
	t_redir		*redir;
	int			special_id;

	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = escape_control((*word_list)->content);
	*word_list = (*word_list)->next;
	if (*word_list)
	{
		special_id = escape_control((*word_list)->content);
		if (special_id != 5 && special_id != 3)
		{
			redir->file = ft_strdup((*word_list)->content);
			*word_list = (*word_list)->next;
		}
	}
	else
		redir->file = NULL;
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
		return (ft_strdup(bin));
	}
	i = 0;
	while (paths[i])
	{
		to_check = ft_calloc(ft_strlen(paths[i]) + ft_strlen(bin) + 2, sizeof(char));
		if (!to_check)
			return (ft_strdup(bin));
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

static void	set_command(t_list	**word_list, t_command *command, t_list *env_var)
{
	command->cmd = find_bin((*word_list)->content, env_var);
	command->name = ft_strdup((*word_list)->content);
	*word_list = (*word_list)->next;
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

t_bool	has_redir_out(t_list *redirs)
{
	t_redir	redir;

	while (redirs)
	{
		redir = *(t_redir *)redirs->content;
		if (redir.type == 1 || redir.type == 4)
			return (true);
		redirs = redirs->next;
	}
	return (false);
}

/*
** retourne l'objet t_command en utilisant les tokens
** jusqu'a rencontrer un token | ou ;
** le premier token a ne pas etre une redirection est considerer
** comme la commande
*/

t_command	*get_command(t_list **word_list, t_list *env_var)
{
	t_command	*command;
	t_bool		command_set;
	int			special_id;

	command = init_command();
	command_set = false;
	if (!command)
		return (NULL);
	while (*word_list)
	{
		special_id = escape_control((*word_list)->content);
		if (special_id == 5 || special_id == 3)
			break ;
		if (special_id == 1 || special_id == 2 || special_id == 4)
			ft_lstadd_back(&command->redirs, ft_lstnew(get_redir(word_list)));
		else if (!command_set)
		{
			command_set = true;
			set_command(word_list, command, env_var);
		}
		else
			ft_lstadd_back(&command->args, ft_lstnew(get_arg(word_list)));
	}
	if (!ft_strcmp(command->name, "ls") && !has_redir_out(command->redirs) && isatty(STDIN_FILENO))
		ft_lstadd_back(&command->args, ft_lstnew(ft_strdup("--color")));
	return (command);
}
