/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_other.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:31:39 by jrocha-f          #+#    #+#             */
/*   Updated: 2025/01/15 15:34:53 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_other(t_command *cmd, t_minishell *master)
{
	int	pid;
	int	status;

	if(!cmd->cmd_path)
		return (1);
	pid = fork();
	if (pid == -1)
	{
		perror("error fork");
		return(1);
	}
	if (pid == 0)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		dup2(cmd->fd_out, STDOUT_FILENO);
		if (cmd->fd_in != STDIN_FILENO)
			close(cmd->fd_in);
		if(cmd->fd_out != STDOUT_FILENO)
			close(cmd->fd_out);
		if (execve(cmd->cmd_path, cmd->cmd, master->env) == -1)
		{
			perror(cmd->cmd[0]);
			master->last_status = 127;
			return (1);
		}
	}
	wait(NULL);
	/*else
		int status;
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid");
		}
		else if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			fprintf(stderr, "Command exited with status %d\n", WEXITSTATUS(status));
		}*/
	return(0);
}