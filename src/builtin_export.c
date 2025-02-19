/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:01:51 by marvin            #+#    #+#             */
/*   Updated: 2025/02/06 14:50:42 by jrocha-f         ###   ########.fr       */
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

static int is_valid_variable(char *var)
{
	int	i;

	i = 0;
	if (!var || !var[0])
		return (0);
	if(ft_isdigit(var[0]) || (!ft_isalnum(var[0]) && var[0] != '_'))
		return(0);
	while(var[i] != '\0' && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return(0);
		i++;
	}
	return(1);
}

static void	ft_change_variable_value(t_minishell *master, char *var, int flag)
{
	t_env	*iter;
	char	*new_var;
	int		i;

	if (flag == 1)
		iter = master->envp;
	else
		iter = master->export;
	i= 0;
	while (var[i] && var[i] != '=')
		i++;
	while (iter)
	{
		if (ft_strncmp(iter->env_var, var, i) == 0 && (iter->env_var[i] == '\0' || iter->env_var[i] == '='))
		{
			new_var = ft_strdup(var);
			if (!new_var)
				return;
			free(iter->env_var);
			iter->env_var = new_var;
			return;
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
	return;
	}
	else if (!master->export)
	{
	master->export = new;
	return;
	}
	while (iter->next != NULL)
		iter = iter->next;
	new->next = iter->next;
	iter->next = new;
}

static int	check_if_var_exist(t_minishell *master, char *var, int flag)
{
	t_env	*iter;
	int		i;

	if (flag == 1)
		iter = master->envp;
	else
		iter = master->export;
	i= 0;
	while (var[i] && var[i] != '=')
		i++;
	while (iter)
	{
		if (ft_strncmp(iter->env_var, var, i) == 0 && (iter->env_var[i] == '=' || iter->env_var[i] == '\0'))
			return (1);
		iter = iter->next;
	}
	return (0);
}

int	ft_export(t_command *cmd, t_minishell *master)
{
	int	i;
	t_env	*iter;

	i = 0;
	if(!cmd->cmd[1])
	{
		print_sorted_env(master);
		return(0);
	}
	while (cmd->cmd[++i])
	{
		if (!is_valid_variable(cmd->cmd[i]))
		{ 
			ft_putstr_fd("export: ", 2);
			ft_putstr_fd(cmd->cmd[i], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			master->last_status = EXIT_FAILURE;
		}
		else
		{
			if (check_if_var_exist(master, cmd->cmd[i], 0) == 0)
			{
				if (ft_strchr(cmd->cmd[i], '='))
					ft_add_env_variable(master, cmd->cmd[i], 1);
				ft_add_env_variable(master, cmd->cmd[i], 0);
			}
			else
			{
				if (ft_strchr(cmd->cmd[i], '=') && check_if_var_exist(master, cmd->cmd[i], 1) == 0)
					ft_add_env_variable(master, cmd->cmd[i], 1);
				else if (ft_strchr(cmd->cmd[i], '='))
					ft_change_variable_value(master, cmd->cmd[i], 1);
				ft_change_variable_value(master, cmd->cmd[i], 0);
			}
		}
	}
	i = 0;
	iter = master->envp;
	while (iter)
	{
		iter = iter->next;
		i++;
	}
	master->env = env_cpy_arr(master->envp, i);
	return (0);
}
