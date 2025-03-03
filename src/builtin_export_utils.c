/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:27:02 by jrocha-f          #+#    #+#             */
/*   Updated: 2025/03/03 10:49:44 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_var_exist(t_minishell *master, char *var, int flag)
{
	t_env	*iter;
	int		i;

	if (flag == 1)
		iter = master->envp;
	else
		iter = master->export;
	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	while (iter)
	{
		if (ft_strncmp(iter->env_var, var, i) == 0 && (iter->env_var[i] == '='
				|| iter->env_var[i] == '\0'))
			return (1);
		iter = iter->next;
	}
	return (0);
}

void	ft_export_error(char *cmd, t_minishell *master)
{
	ft_putstr_fd("export: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
	master->last_status = EXIT_FAILURE;
}

int	is_valid_variable(char *var)
{
	int	i;

	i = 0;
	if (!var || !var[0])
		return (0);
	if (ft_isdigit(var[0]) || (!ft_isalnum(var[0]) && var[0] != '_'))
		return (0);
	while (var[i] != '\0' && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
