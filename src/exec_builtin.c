/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:19:04 by jrocha-f          #+#    #+#             */
/*   Updated: 2025/02/19 12:43:46 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *command)
{
	if (ft_strncmp(command, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(command, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(command, "pwd", 5) == 0)
		return (1);
	if (ft_strncmp(command, "env", 4) == 0)
		return (1);
	if (ft_strncmp(command, "export", 7) == 0)
		return (1);
	if (ft_strncmp(command, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(command, "exit", 5) == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_command *cmd, t_minishell *master)
{
	int	result;

	result = 0;
	if (ft_strncmp(cmd->cmd[0], "echo", 5) == 0)
		result = ft_echo(cmd);
	if (ft_strncmp(cmd->cmd[0], "cd", 3) == 0)
		result = ft_cd(cmd, master);
	if (ft_strncmp(cmd->cmd[0], "pwd", 4) == 0)
		result = ft_pwd(cmd);
	if (ft_strncmp(cmd->cmd[0], "export", 7) == 0)
		ft_export(cmd, master);
	if (ft_strncmp(cmd->cmd[0], "unset", 6) == 0)
		ft_unset(cmd, master);
	if (ft_strncmp(cmd->cmd[0], "env", 4) == 0)
		result = ft_env(cmd, master);
	if (ft_strncmp(cmd->cmd[0], "exit", 5) == 0)
		ft_exit(cmd, master);
	master->last_status = result;
	return (result);
}
