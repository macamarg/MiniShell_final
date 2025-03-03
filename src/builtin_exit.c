/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:03:45 by marvin            #+#    #+#             */
/*   Updated: 2025/03/03 13:40:13 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
 * exit the shell
 * if numeric parameter - exit with that code
 */

static void	error_exit(t_command *cmd, t_minishell *master)
{
	ft_putstr_fd("exit\nminishell: exit:", 2);
	ft_putstr_fd(cmd->cmd[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	master->last_status = 2;
	ft_clean_ms(master);
	exit(2);
}

int	ft_is_number(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (str[0] == '-' || str[0] == '+')
		i = 1;
	else
		i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_command *cmd, t_minishell *master)
{
	int	status;

	printf("exit\n");
	if (cmd->cmd[1])
	{
		if (!ft_is_number(cmd->cmd[1]))
			error_exit(cmd, master);
		if (cmd->cmd[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (1);
		}
		status = ft_atoi(cmd->cmd[1]);
		status %= 256;
	}
	else
		status = master->last_status;
	ft_clean_ms(master);
	exit (status);
}
