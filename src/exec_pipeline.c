/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:59:24 by marvin            #+#    #+#             */
/*   Updated: 2025/03/10 13:47:48 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	exec_builtin_pipeline(t_minishell *master, t_command *start, int *fd_pipe,
							int prev_read_fd)
{
	if (start->order == FIRST && start->redir_in == NULL)
		start->fd_in = STDIN_FILENO;
	else if (start->redir_in == NULL)
		start->fd_in = prev_read_fd;
	if (start->order == LAST && start->redir_out == NULL)
		start->fd_out = STDOUT_FILENO;
	else if (start->redir_out == NULL)
		start->fd_out = fd_pipe[WRITE_END];
	return (exec_builtin(start, master));
}

static void	child_process(t_minishell *master, t_command *start, int *fd_pipe,
							int prev_read_fd)
{
	if (start->order == FIRST)
		handle_fd_first(master, start, fd_pipe, prev_read_fd);
	else if (start->order == MIDLE)
		handle_fd_middle(master, start, fd_pipe, prev_read_fd);
	else
		handle_fd_last(master, start, fd_pipe, prev_read_fd);
	if (start->fd_in != STDIN_FILENO)
		close(start->fd_in);
	if (start->fd_out != STDOUT_FILENO)
		close(start->fd_out);
	close_pipe(fd_pipe);
	if (prev_read_fd != -1)
		close(prev_read_fd);
	if (is_builtin(start->cmd[0]))
	{
		exec_builtin_pipeline(master, start, fd_pipe, prev_read_fd);
		ft_clean_ms(master);
		exit(master->last_status);
	}
	if (execve(start->cmd_path, start->cmd, master->env) == -1)
	{
		perror(start->cmd[0]);
		exit(master->last_status);
	}
}

void	exec_pipeline(t_minishell *master, t_command *cmd_lst)
{
	t_command	*start;
	int			pid;
	int			fd_pipe[2];
	int			prev_read_fd;
	int			last_pid;

	prev_read_fd = -1;
	start = cmd_lst;
	while (start)
	{	
		if(start->cmd && !only_spaces(start->cmd[0]))
		{
			if (pipe(fd_pipe) < 0)
				return (perror("pipe"));
			pid = fork();
			if (pid == -1)
				return (perror("fork"));
			if (pid == 0)
				child_process(master, start, fd_pipe, prev_read_fd);
			ignore_signals_init();
			last_pid = pid;
			parent_cleanup(&prev_read_fd, fd_pipe, start);
		}
		start = start->next;
	}
	if (prev_read_fd != -1)
		close(prev_read_fd);
	wait_for_pipeline(master, last_pid);
}
