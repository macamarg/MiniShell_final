/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:59:24 by marvin            #+#    #+#             */
/*   Updated: 2025/03/24 10:35:42 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	pipe_clean_and_exit(t_minishell *master, int exit_status)
{
	close_cmd_list_fds(master->cmd_lst);
	ft_clean_ms(master);
	exit(126);
}

void	wait_for_pipeline(t_minishell *master, int last_pid)
{
	int	status;
	int	pid;
	int	last_failed_status;

	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				master->last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				master->last_status = 128 + WTERMSIG(status);
		}
		pid = wait(&status);
	}
}

static void	child_process(t_minishell *master, t_command *start, int *fd_pipe,
							int prev_read_fd)
{
	ft_choose_handle (master, start, fd_pipe, prev_read_fd);
	close_pipe(fd_pipe);
	if (prev_read_fd != -1)
		close(prev_read_fd);
	if (is_builtin(start->cmd[0]))
	{
		exec_builtin(start, master);
		pipe_clean_and_exit (master, master->last_status);
	}
	if (!start->cmd_path)
		pipe_clean_and_exit (master, 127);
	if (execve(start->cmd_path, start->cmd, master->env) == -1)
	{
		perror(start->cmd[0]);
		pipe_clean_and_exit (master, master->last_status);
	}
}

void	handle_pipeline(t_minishell *master, t_command *start,
						int *prev_read_fd, int *last_pid)
{
	int	fd_pipe[2];
	int	pid;

	if (pipe(fd_pipe) < 0)
		return (perror("pipe"));
	pid = fork();
	if (pid == -1)
		return (perror("fork"));
	if (pid == 0)
		child_process(master, start, fd_pipe, *prev_read_fd);
	ignore_signals_init();
	*last_pid = pid;
	parent_cleanup(prev_read_fd, fd_pipe, start);
}

void	exec_pipeline(t_minishell *master, t_command *cmd_lst)
{
	t_command	*start;
	int			prev_read_fd;
	int			last_pid;

	prev_read_fd = -1;
	start = cmd_lst;
	while (start)
	{
		if (start->cmd && !only_spaces(start->cmd[0]))
			handle_pipeline(master, start, &prev_read_fd, &last_pid);
		start = start->next;
	}
	if (prev_read_fd != -1)
		close(prev_read_fd);
	wait_for_pipeline(master, last_pid);
}
