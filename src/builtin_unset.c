/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:11:26 by marvin            #+#    #+#             */
/*   Updated: 2025/02/06 14:57:02 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
 * Each variable or function specified by name shall be unset.
 * Unsetting a variable or function that was not previously set
 * shall not be considered an error and does not cause the shell to
 * abort.
*/

static void	remove_env_node(t_minishell *master, t_env *node, int env_flag)
{
	t_env	*iter;

	if (env_flag == true)
		iter = master->envp;
	else
		iter = master->export;
	if (!iter || !node)
		return;
	if (iter == node)
	{
		if (iter == node)
		{
			if (env_flag)
				master->envp = node->next;
			else
				master->export = node->next;
			free(node->env_var);
			free(node);
			return;
		}
	}
	while (iter && iter->next)
	{
		if (iter->next == node)
		{
			iter->next = node->next;
			free(node->env_var);
			free(node);
			return;
		}
		iter = iter->next;
	}
}

t_env	*check_if_exists(char *cmd, t_minishell *master, int env_flag)
{
	int 	h;
	int		len_cmd;
	bool	equal_flag;
	t_env	*iter;

	if (env_flag == true)
		iter = master->envp;
	else
		iter = master->export;
	len_cmd = ft_strlen(cmd);
	equal_flag = false;
	while (iter)
	{
		h = 0;
		if (ft_strnstr(cmd, "=", len_cmd))
			equal_flag = true;
		if (equal_flag)
		{
			if (ft_strlen(iter->env_var) == len_cmd && ft_strncmp(iter->env_var, cmd, len_cmd + 1) == 0)
				return (iter);
		}
		else
		{
			while (iter->env_var[h] != '=' && iter->env_var[h] != '\0')
				h++;
			if (ft_strncmp(iter->env_var, cmd, h) == 0)
				return(iter);
		}
	iter = iter->next;
	}
	return(NULL);
}

int	ft_unset(t_command *cmd, t_minishell *master)
{
	int		i;
	int		envp_size;
	int		len_cmd;
	int		env_flag;
	t_env	*iter;

	i = true;
	while (cmd->cmd[i])
	{
		env_flag = true;
		while(env_flag >= 0)
		{
			iter = check_if_exists(cmd->cmd[i], master, env_flag);
			if (iter)
				remove_env_node(master, iter, env_flag);
			env_flag--;
		}
		i++;
	}
	master->env = env_cpy_arr(master->envp, env_count(master->envp));
	return (0);
}
