/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 13:02:57 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/04 12:00:16 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <sys/types.h>
#include <sys/wait.h>

/*
** DEMO POUR LES PIPES
*/

typedef int t_tube[2];


/*
** Donc, on a besoin de link les process avec des pipes
** Je fais un liste de pipes t_pipe[2]
**
** (fd 0)--> Process 1 --> pipes(3 -> 4) --> Process 2 --> pipes(5 -> 6) --> process
** pipe_n = command_n - 1
** pip[0] -> read
** pip[1] -> write
** dup2 close la source;
*/

void	close_unused_fds(int index, int	size, t_tube *tube_list)
{
	int		i;

	i = 0;
	while (i < (index - 1))
	{
		close(tube_list[i][0]);
		close(tube_list[i][1]);
		i++;
	}
	if (index != 0)
	{
		close(tube_list[i++][1]);
	}
	if (i < size)
	{
		close(tube_list[i++][0]);
	}
	while (i < size)
	{
		close(tube_list[i][0]);
		close(tube_list[i][1]);
		i++;
	}
}

void	close_all_pipes(t_tube *tube_list, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		close(tube_list[i][0]);
		close(tube_list[i][1]);
		i++;
	}
}

void	exec_pipes(char ***commands)
{
	t_tube	*tube_list;
	pid_t	pid;
	int		fork_n;
	int		i;

	fork_n = 0;
	while (commands[fork_n]) /* on compte le nombre de fork */
		fork_n++;
	tube_list = calloc(fork_n - 1, sizeof(t_tube)); /* on alloc le nombre de tube voulu (fork_n - 1) */
	i = 0;
	while (i < (fork_n - 1))
		pipe(tube_list[i++]); /* On pipes tous les tubes */
	i = 0;
	while (commands[i])
	{
		pid = fork();
		if (pid == 0) /* on verifie si on est dans le child */
		{
			close_unused_fds(i, (fork_n - 1), tube_list); /* on close tous les fd inutiles */
			if (i != 0)
				dup2(tube_list[i - 1][0], STDIN_FILENO);
			if (i < (fork_n - 1))
				dup2(tube_list[i][1], STDOUT_FILENO);
			execvp(commands[i][0], commands[i]);
		}
		i++;
	}
	close_all_pipes(tube_list, fork_n - 1);
	while (fork_n)
	{
		int		status;
		pid_t	pid = wait(&status);
		printf("Fork with PID: %i quited with status: %i\n", pid, status);
		fork_n--;
	}
	free(tube_list);
	read(0, NULL, 1);
}


int		main(void)
{
	char *cmd1[] = {"cat", "/dev/urandom", NULL};

	char **cmds[] = {cmd1, NULL};
	exec_pipes(cmds);
}
