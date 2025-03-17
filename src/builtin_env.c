/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macamarg <macamarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:09:33 by marvin            #+#    #+#             */
/*   Updated: 2025/03/17 10:00:22 by macamarg         ###   ########.fr       */
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
	if (!master->env)
		return (1);
	while (master->env[++i])
		printf("%s\n", master->env[i]);
	return (0);
}
