/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:59:24 by marvin            #+#    #+#             */
/*   Updated: 2025/02/17 15:11:05 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_pipe(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

static void	parent_cleanup(int prev_read_fd, int *fd_pipe)
{
	close(fd_pipe[WRITE_END]);
	if (prev_read_fd != -1)
		close(prev_read_fd);
}

static void	child_process(t_minishell *master, t_command *start, int *fd_pipe,
							int prev_read_fd)
{
	if (start->order == FIRST)
	{
		if (start->fd_in != STDIN_FILENO)
			dup2(start->fd_in, STDIN_FILENO);
		if (start->redir_out != NULL && start->fd_out != STDOUT_FILENO)
			dup2(start->fd_out, STDOUT_FILENO);
		else
			dup2(fd_pipe[WRITE_END], STDOUT_FILENO);
	}
	else if (start->order == MIDLE)
	{
		if (start->redir_in != NULL && start->fd_in != STDIN_FILENO)
			dup2(start->fd_in, STDIN_FILENO);
		else if (prev_read_fd != -1)
			dup2(prev_read_fd, STDIN_FILENO);
		if (start->redir_out != NULL && start->fd_out != STDOUT_FILENO)
			dup2(start->fd_out, STDOUT_FILENO);
		else
			dup2(fd_pipe[WRITE_END], STDOUT_FILENO);
	}
	else
	{
		if (start->redir_in != NULL && start->fd_in != STDIN_FILENO)
			dup2(start->fd_in, STDIN_FILENO);
		else if (prev_read_fd != -1)
			dup2(prev_read_fd, STDIN_FILENO);
		if (start->redir_out != NULL && start->fd_out != STDOUT_FILENO)
			dup2(start->fd_out, STDOUT_FILENO);
	}
	if (start->fd_in != STDIN_FILENO)
		close(start->fd_in);
	if (start->fd_out != STDOUT_FILENO)
		close(start->fd_out);
	close_pipe(fd_pipe);
	if (prev_read_fd != -1)
		close(prev_read_fd);
}

int	exec_builtin_pipeline (t_minishell *master, t_command *start, int *fd_pipe,
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

void	exec_pipeline(t_minishell *master, t_command *cmd_lst)
{
	t_command	*start;
	int			pid;
	int			fd_pipe[2];
	int			prev_read_fd;

	prev_read_fd = -1;
	start = cmd_lst;
	while (start)
	{
		if (pipe(fd_pipe) < 0)
			{
				perror("pipe");
				return ;
			}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return ;
		}
		if (pid == 0)
		{
			child_process(master, start, fd_pipe, prev_read_fd);
			if (is_builtin(start->cmd[0]))
			{
				exec_builtin_pipeline(master, start, fd_pipe, prev_read_fd);
				exit(master->last_status);
			}
			if (execve(start->cmd_path, start->cmd, master->env) == -1)
			{
				perror(start->cmd[0]);
				exit(master->last_status);
			}
		}
	close(fd_pipe[WRITE_END]);
	if (prev_read_fd != -1)
		close(prev_read_fd);
	prev_read_fd = fd_pipe[READ_END];
	if (start->fd_in != STDIN_FILENO)
		close(start->fd_in);
	if (start->fd_out != STDOUT_FILENO)
		close(start->fd_out);
	//parent_cleanup(prev_read_fd, fd_pipe);
	start = start->next;
	}
	if (prev_read_fd != -1)
		close(prev_read_fd);
	while (wait(NULL) > 0)
		;
}