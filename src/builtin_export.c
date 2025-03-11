/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:01:51 by marvin            #+#    #+#             */
/*   Updated: 2025/03/11 11:35:01 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
 * give the export attribute to the variables
 * corresponding to the specified names, which shall cause them to
 * be in the environment of subsequently executed commands. If the
 * name of a variable is followed by =word, then the value of that
 * variable shall be set to word.
*/

void	ft_change_variable_value(t_minishell *master, char *var, int flag)
{
	t_env	*iter;
	char	*new_var;
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
		if (ft_strncmp(iter->env_var, var, i) == 0 && (iter->env_var[i] == '\0'
				|| iter->env_var[i] == '='))
		{
			new_var = ft_strdup(var);
			if (!new_var)
				return ;
			free(iter->env_var);
			iter->env_var = new_var;
			return ;
		}
		iter = iter->next;
	}
}

static void	ft_add_env_variable(t_minishell *master, char *var, int flag)
{
	t_env	*new;
	t_env	*iter;

	if (flag == 1)
		iter = master->envp;
	else
		iter = master->export;
	new = safe_malloc(sizeof(t_env));
	new->env_var = ft_strdup(var);
	new->next = NULL;
	if (flag == 1 && !master->envp)
	{
		master->envp = new;
		return ;
	}
	else if (!master->export)
	{
		master->export = new;
		return ;
	}
	while (iter->next != NULL)
		iter = iter->next;
	new->next = iter->next;
	iter->next = new;
}

void	ft_execute_export(char *cmd, t_minishell *master)
{
	if (check_if_var_exist(master, cmd, 0) == 0)
	{
		if (ft_strchr(cmd, '='))
			ft_add_env_variable(master, cmd, 1);
		ft_add_env_variable(master, cmd, 0);
	}
	else
	{
		if (ft_strchr(cmd, '=') && check_if_var_exist(master, cmd, 1) == 0)
			ft_add_env_variable(master, cmd, 1);
		else if (ft_strchr(cmd, '='))
			ft_change_variable_value(master, cmd, 1);
		ft_change_variable_value(master, cmd, 0);
	}
}

int	ft_export(t_command *cmd, t_minishell *master)
{
	int		i;
	t_env	*iter;
	char	*unquoted;

	i = 0;
	if (!cmd->cmd[1])
	{
		print_sorted_env(master);
		return (0);
	}
	while (cmd->cmd[++i])
	{
		unquoted = rm_quotes_str(cmd->cmd[i]);
		if (!is_valid_variable(unquoted))
		{
			ft_export_error(unquoted, master);
			free(unquoted);
			return (1);
		}
		else
			ft_execute_export(unquoted, master);
		free(unquoted);
	}
	i = env_count(master->envp);
	free_array(master->env);
	master->env = env_cpy_arr(master->envp, i);
	return (0);
}
