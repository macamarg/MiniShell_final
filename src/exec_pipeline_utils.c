/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:47:43 by jrocha-f          #+#    #+#             */
/*   Updated: 2025/03/03 15:07:49 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_fd_first(t_minishell *master, t_command *start, int *fd_pipe,
							int prev_read_fd)
{
	if (start->fd_in != STDIN_FILENO)
		dup2(start->fd_in, STDIN_FILENO);
	if (start->redir_out != NULL && start->fd_out != STDOUT_FILENO)
		dup2(start->fd_out, STDOUT_FILENO);
	else
		dup2(fd_pipe[WRITE_END], STDOUT_FILENO);
}

void	handle_fd_middle(t_minishell *master, t_command *start, int *fd_pipe,
							int prev_read_fd)
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

void	handle_fd_last(t_minishell *master, t_command *start, int *fd_pipe,
							int prev_read_fd)
{
	if (start->redir_in != NULL && start->fd_in != STDIN_FILENO)
		dup2(start->fd_in, STDIN_FILENO);
	else if (prev_read_fd != -1)
		dup2(prev_read_fd, STDIN_FILENO);
	if (start->redir_out != NULL && start->fd_out != STDOUT_FILENO)
		dup2(start->fd_out, STDOUT_FILENO);
}

void	close_pipe(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void	parent_cleanup(int *prev_read_fd, int *fd_pipe, t_command *start)
{
	close(fd_pipe[WRITE_END]);
	if (*prev_read_fd != -1)
		close(*prev_read_fd);
	*prev_read_fd = fd_pipe[READ_END];
	if (start->fd_in != STDIN_FILENO)
		close(start->fd_in);
	if (start->fd_out != STDOUT_FILENO)
		close(start->fd_out);
}
