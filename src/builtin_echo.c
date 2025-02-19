/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:19:29 by jrocha-f          #+#    #+#             */
/*   Updated: 2025/02/19 12:00:45 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Display message on screen, writes each given STRING to standard output,
 * with a space between each and a newline after the last one.
 *
 * -n	Do not output a trailing newline.
*/

#include "../minishell.h"

static void	echo_text(t_command *cmd, int i)
{
	while (cmd->cmd[i])
	{
		ft_putstr_fd(cmd->cmd[i], cmd->fd_out);
		if (cmd->cmd[i + 1])
			ft_putchar_fd(' ', cmd->fd_out);
		i++;
	}
}

static bool	is_n_flag(char *cmd)
{
	int	i;

	i = 1;
	if (!ft_strncmp(cmd, "-n", 3))
		return (1);
	else if (!ft_strncmp(cmd, "-n", 2))
	{
		while (cmd[++i])
		{
			if (cmd[i] != 'n')
				return (0);
		}
		return (1);
	}
	else
		return (0);
}

int	ft_echo(t_command *cmd)
{
	int		i;
	bool	flag;

	i = 1;
	flag = false;
	while (cmd->cmd[i] && is_n_flag(cmd->cmd[i]))
	{
		flag = true;
		i++;
	}
	if (!cmd->cmd[i])
	{
		if (!flag)
			ft_putchar_fd('\n', cmd->fd_out);
		return (0);
	}
	echo_text(cmd, i);
	if (!flag)
		ft_putchar_fd('\n', cmd->fd_out);
	return (0);
}
