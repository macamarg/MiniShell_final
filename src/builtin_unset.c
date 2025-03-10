/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:11:26 by marvin            #+#    #+#             */
/*   Updated: 2025/03/10 14:25:40 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
 * Each variable or function specified by name shall be unset.
 * Unsetting a variable or function that was not previously set
 * shall not be considered an error and does not cause the shell to
 * abort.
*/

t_env	*set_iter(t_minishell *master, int env_flag)
{
	t_env	*iter;

	if (env_flag == true)
		iter = master->envp;
	else
		iter = master->export;
	return (iter);
}

static void	remove_first_node(t_minishell *master, t_env *node, int env_flag)
{
	if (env_flag)
		master->envp = node->next;
	else
		master->export = node->next;
	free(node->env_var);
	free(node);
}

static void	remove_env_node(t_minishell *master, t_env *node, int env_flag)
{
	t_env	*iter;

	iter = set_iter(master, env_flag);
	if (!iter || !node)
		return ;
	if (iter == node)
	{
		remove_first_node(master, node, env_flag);
		return ;
	}
	while (iter && iter->next)
	{
		if (iter->next == node)
		{
			iter->next = node->next;
			free(node->env_var);
			free(node);
			return ;
		}
		iter = iter->next;
	}
}

t_env	*find_node(char *cmd, t_minishell *master, int env_flag)
{
	int		h;
	int		len_cmd;
	bool	equal_flag;
	t_env	*iter;

	iter = set_iter(master, env_flag);
	len_cmd = ft_strlen(cmd);
	equal_flag = (ft_strnstr(cmd, "=", len_cmd) != NULL);
	while (iter)
	{
		h = 0;
		if (equal_flag && ft_strlen(iter->env_var) == len_cmd
			&& ft_strncmp(iter->env_var, cmd, len_cmd + 1) == 0)
			return (iter);
		while (!equal_flag
			&& iter->env_var[h] != '=' && iter->env_var[h] != '\0')
			h++;
		if (!equal_flag && ft_strncmp(iter->env_var, cmd, h) == 0)
			return (iter);
		iter = iter->next;
	}
	return (NULL);
}

int	ft_unset(t_command *cmd, t_minishell *master)
{
	int		i;
	int		env_flag;
	t_env	*iter;

	i = 1;
	while (cmd->cmd[i])
	{
		env_flag = true;
		while (env_flag >= 0)
		{
			iter = find_node(cmd->cmd[i], master, env_flag);
			if (iter)
				remove_env_node(master, iter, env_flag);
			env_flag--;
		}
		i++;
	}
	free_array(master->env);
	master->env = env_cpy_arr(master->envp, env_count(master->envp));
	return (0);
}
