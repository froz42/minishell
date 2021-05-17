/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 14:12:05 by tmatis            #+#    #+#             */
/*   Updated: 2021/05/17 21:51:37 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>


void	sig_handler(int signal_no)
{
	(void)signal_no;
}

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

int	build_in(char **argv, t_list **env_var)
{
	int		argc;

	argc = build_argc(argv);
	if (ft_strcmp(argv[0], "cd") == 0)
		return (ft_cd(argc, argv, env_var) + 2);
	else if (ft_strcmp(argv[0], "exit") == 0)
		return (ft_exit(argc, argv, env_var, true) + 2);
	else if (ft_strcmp(argv[0], "echo") == 0)
		return (ft_echo(argc, argv) + 2);
	else if (ft_strcmp(argv[0], "env") == 0)
		return (ft_env(*env_var) + 2);
	else if (ft_strcmp(argv[0], "unset") == 0)
		return (ft_unset(argc, argv, env_var) + 2);
	else if (ft_strcmp(argv[0], "export") == 0)
		return (ft_export(argc, argv, env_var) + 2);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		return (ft_pwd() + 2);
	else
		return (0);
}

void	execution_error_write(char *cmd, char *error)
{
	ft_putstr_fd("Minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	handle_status(int status, t_list **env_var)
{
	char *status_str;
	int	 return_value;

	return_value = 0;
	if (WIFEXITED(status))
		return_value = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		return_value = WTERMSIG(status) + 128;
		if (return_value == 130)
			ft_putstr("\n");
		if (return_value == 131)
			ft_putstr("Quit (core dumped)\n");
		if (return_value == 139)
			ft_putstr("Segmentation fault (core dumped)\n");
	}
	status_str = ft_itoa(return_value);
	edit_var(env_var, "?", status_str);
	free(status_str);
}

t_bool	is_directory(const char *path) {
   struct stat	statbuf;

   if (stat(path, &statbuf) != 0)
       return (true);
   return (S_ISDIR(statbuf.st_mode));
}

int		execution_rules(t_command command, t_list **env_vars)
{
	char		**argv;
	char		**envp;
	int			return_value;
	int			backup[2];

	return_value = 0;
	if (!ft_strcmp(command.name, "ls") && isatty(STDOUT_FILENO))
		ft_lstadd_back(&command.args, ft_lstnew("-G"));
	argv = build_argv(command.name, command.args);
	envp = build_env(*env_vars);
	if (redirect_fd(command, backup))
		return_value = 1 + 2;
	if (!return_value)
		return_value = build_in(argv, env_vars);
	if (!return_value && !command.cmd)
	{
		execution_error_write(command.name, "command not found");
		return_value = 127 + 2;
	}
	if (!return_value)
	{
		if (is_directory(command.cmd))
		{
			execution_error_write(command.name, "Is a directory");
			return_value = 126 + 2;
		}
	}
	if (!return_value)
	{

		execve(command.cmd, argv, envp);
		execution_error_write(argv[0], strerror(errno));
		return_value = 127 + 2;
	}
	free_table(&argv);
	free_table(&envp);
	dup2(backup[0], STDIN_FILENO);
	dup2(backup[1], STDOUT_FILENO);
	close(backup[0]);
	close(backup[1]);
	return (return_value);
}

int		exec_pipes(t_list *pipes_list, t_list **env_vars)
{
	t_tube		*tube_list;
	pid_t		last_pid;
	pid_t		pid;
	int			fork_n;
	int			i;
	int			status;
	int			return_value;

	fork_n = ft_lstsize(pipes_list);
	tube_list = calloc(fork_n - 1, sizeof(t_tube));
	i = 0;
	while (i < (fork_n - 1))
		pipe(tube_list[i++]);
	i = 0;
	while (pipes_list)
	{
		last_pid = fork();
		return_value = 0;
		if (last_pid == 0)
		{
			close_unused_fds(i, (fork_n - 1), tube_list);
			if (i != 0)
				dup2(tube_list[i - 1][0], STDIN_FILENO);
			if (i < (fork_n -1))
				dup2(tube_list[i][1], STDOUT_FILENO);
			return_value = execution_rules(*(t_command *)pipes_list->content, env_vars);
			if (i < (fork_n -1))
				close(tube_list[i][1]);
			if (i != 0)
				close(tube_list[i - 1][0]);
			free(tube_list);
			return (return_value);
		}
		i++;
		pipes_list = pipes_list->next;
	}
	close_all_pipes(tube_list, fork_n - 1);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	while (fork_n)
	{
		pid = wait(&status);
		if (pid == last_pid)
			handle_status(status, env_vars);
		fork_n--;
	}
	free(tube_list);
	return (0);
}
