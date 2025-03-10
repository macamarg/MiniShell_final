/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_level.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:19:58 by jrocha-f          #+#    #+#             */
/*   Updated: 2025/03/10 14:30:54 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_shell_level(t_minishell *master)
{
	int		shlvl;
	t_env	*iter;

	iter = master->envp;
	while (iter != NULL)
	{
		if (ft_strlen(iter->env_var) >= 6
			&& ft_strncmp("SHLVL=", iter->env_var, 6) == 0)
			break ;
		iter = iter->next;
	}
	shlvl = atoi(iter->env_var + 6);
	return (shlvl);
}

void	add_shell_level(t_minishell *master)
{
	int		shlvl;
	int		i;
	char	*new_shlvl;
	char	*str_shlvl;
	t_env	*iter;

	shlvl = find_shell_level(master) + 1;
	str_shlvl = ft_itoa(shlvl);
	new_shlvl = ft_strjoin("SHLVL=", str_shlvl);
	free(str_shlvl);
	ft_change_variable_value(master, new_shlvl, 1);
	ft_change_variable_value(master, new_shlvl, 0);
	free(new_shlvl);
	i = 0;
	iter = master->envp;
	while (iter)
	{
		iter = iter->next;
		i++;
	}
	free_array(master->env);
	master->env = env_cpy_arr(master->envp, i);
}
