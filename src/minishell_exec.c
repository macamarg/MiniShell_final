/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:58:05 by jrocha-f          #+#    #+#             */
/*   Updated: 2025/03/03 14:58:39 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
 * is a buit in?
 *  call it
 * else -> fork + execve + wait
*/

void	exec_cmd(t_minishell *master, t_command *cmd)
{
	if (is_builtin(cmd->cmd[0]))
		exec_builtin((cmd), master);
	else
		exec_other((cmd), master);
}

int	check_cmd(t_minishell *master, t_command *cmd)
{
	if (!cmd->cmd_path)
	{
		error_cmdnfound(master, cmd->cmd);
		return (1);
	}
	return (0);
}

void	fill_cmd(t_minishell *master, t_command *cmd_lst)
{
	t_command	*current;

	current = cmd_lst;
	while (current != NULL)
	{
		if (!is_builtin(current->cmd[0]))
			current->cmd_path = get_cmdpath(master, current);
		if (current->prev == NULL)
			current->order = FIRST;
		else if (current->next == NULL)
			current->order = LAST;
		else
			current->order = MIDLE;
		current = current->next;
	}
}

void	mini_exec(t_minishell *master)
{
	if (!master->cmd_lst || !(*master->cmd_lst) || !(*master->cmd_lst)->cmd
		|| !(*master->cmd_lst)->cmd[0])
		return ;
	else
	{
		fill_cmd(master, *(master->cmd_lst));
		if ((*master->cmd_lst)->pipe == 0)
			exec_cmd(master, *(master->cmd_lst));
		else
			exec_pipeline(master, *(master->cmd_lst));
	}
}
