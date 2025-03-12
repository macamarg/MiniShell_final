/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_other.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:31:39 by jrocha-f          #+#    #+#             */
/*   Updated: 2025/03/12 10:02:21 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	wait_for_child(t_minishell *master, int pid)
{
	int	status;

	ignore_signals_init();
	if (waitpid(pid, &status, 0) == -1)
		perror("waitpid");
	else if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		master->last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		master->last_status = 128 + WTERMSIG(status); //neds testing
}

static void	child_handle_fd(t_command *cmd, t_minishell *master)
{
	dup2(cmd->fd_in, STDIN_FILENO);
	dup2(cmd->fd_out, STDOUT_FILENO);
	if (cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	if (cmd->fd_out != STDOUT_FILENO)
		close(cmd->fd_out);
}

int	exec_other(t_command *cmd, t_minishell *master)
{
	int	pid;

	if (!cmd->cmd_path)
	{
		//error_cmdnfound(master, cmd->cmd);
		master->last_status = 127;
		return (1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("error fork");
		return (1);
	}
	if (pid == 0)
	{
		child_signals_init();
		child_handle_fd(cmd, master);
		if (execve(cmd->cmd_path, cmd->cmd, master->env) == -1)
		{
			perror(cmd->cmd[0]);
			master->last_status = 127;
			exit (127);
		}
	}
	else
		wait_for_child(master, pid);
	return (0);
}
