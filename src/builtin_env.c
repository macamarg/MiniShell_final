/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:09:33 by marvin            #+#    #+#             */
/*   Updated: 2025/02/19 12:05:37 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * print a list of environment variables
*/

#include "../minishell.h"

int	ft_env(t_command *cmd, t_minishell *master)
{
	int	i;

	i = -1;
	if (cmd->cmd[1])
	{
		ft_putstr_fd("env:", 2);
		ft_putstr_fd(cmd->cmd[1], 2);
		ft_putstr_fd("No such file or directory \n", 2);
		return (127);
	}
	while (master->env[++i])
		printf("%s\n", master->env[i]);
	return (0);
}
