/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:15:36 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/23 14:34:22 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Permet de free l'objet t_redir dans une liste chainee
*/

void	free_redir(void *mem)
{
	t_redir	*redir;

	if (mem)
	{
		redir = (t_redir *)mem;
		if (redir->file)
			free(redir->file);
		free(mem);
	}
}

/*
** Permet de free l'objet t_command dans une liste chainee
*/

void	free_command(void *mem)
{
	t_command	*command;

	if (!mem)
		return ;
	command = (t_command *)mem;
	ft_safe_free(command->cmd);
	ft_safe_free(command->name);
	ft_lstclear(&command->args, ft_safe_free);
	ft_lstclear(&command->redirs, free_redir);
	ft_safe_free(command);
}

/*
** Permet de free la liste de t_command
*/

void	free_command_list(void *mem)
{
	t_list	*list;

	list = (t_list *)mem;
	ft_lstclear(&list, free_command);
}

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
