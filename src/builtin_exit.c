/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:03:45 by marvin            #+#    #+#             */
/*   Updated: 2025/02/07 12:03:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
 * exit the shell
 if numeric parameter - exit with that code
 */

int ft_is_number(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

 int ft_exit(t_command *cmd, t_minishell *master)
 {
	int	status;

	if (cmd->cmd[1])
	{
		if (cmd->cmd[2])
		{
			ft_putstr_fd("exit\n minishell: exit: too many arguments\n", 2);
			master->last_status = 1;
		}
		if (ft_is_number(cmd->cmd[1]))
		{
			status = ft_atoi(cmd->cmd[1]);
			ft_clean_ms(master);
			exit(status);
		}
		else
		{
			ft_putstr_fd("exit\nminishell: exit:", 2);
			ft_putstr_fd(cmd->cmd[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			master->last_status = 2;
			ft_clean_ms(master);
			exit(2);
		}
	}
	//ALTERAR SHEL LEVL
	status = master->last_status;
	ft_clean_ms(master);
	exit(status);
 }
