/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_level.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:19:58 by jrocha-f          #+#    #+#             */
/*   Updated: 2025/02/19 11:10:13 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_shell_level (t_minishell *master)
{
	int		shlvl;
	t_env	*iter;

	iter = master->envp;
	while(iter!= NULL)
	{
		if(ft_strlen(iter->env_var) >= 6 && ft_strncmp("SHLVL=", iter->env_var, 6) == 0)
			break;
		iter = iter->next;
	}
	shlvl = atoi(iter->env_var + 6);
	return(shlvl);
}

void	add_shell_level(t_minishell *master)
{
	int		shlvl;
	int		i;
	char	*new_shlvl;
	t_env	*iter;

	shlvl = find_shell_level (master) + 1;
	new_shlvl = ft_strjoin("SHLVL=", ft_itoa(shlvl));
	ft_change_variable_value(master, new_shlvl, 1);
	ft_change_variable_value(master, new_shlvl, 0);
	i = 0;
	iter = master->envp;
	while (iter)
	{
		iter = iter->next;
		i++;
	}
	master->env = env_cpy_arr(master->envp, i);
}