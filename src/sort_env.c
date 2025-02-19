/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:34:01 by jrocha-f          #+#    #+#             */
/*   Updated: 2025/02/11 12:59:59 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void	swap_nodes(t_env **export, t_env	*node)
{
	t_env	*prev;
	t_env	*next;

	if (!export || !*export || !node || !node->next)
		return;
	next = node->next;
	if(*export == node)
	{
		*export = next;
		node->next = next->next;
		next->next = node;
		return;
	}
	prev = *export;
	while(prev->next && prev->next != node)
		prev = prev->next;
	prev->next = next;
	node->next = next->next;
	next->next = node;
}

static void	env_cpy_export(t_minishell *master, char **env)
{
	int	i;
	t_env	*tmp;
	t_env	*iter;

	i = -1;
	while (env[++i])
	{
		tmp = safe_malloc(sizeof(t_env));
		tmp->env_var = ft_strdup(env[i]);
		tmp->next = NULL;
		if (master->export == NULL)
			master->export = tmp;
		else
		{
			iter = master->export;
			while (iter->next != NULL)
			{
				iter = iter->next;
			}
			iter->next = tmp;
		}
	}
}

void	*sort_env(t_minishell *master, char **env)
{
	t_env	*export;
	t_env	*iter;

	if(!master->export)
		env_cpy_export(master, master->env);
	iter = master->export;
	while(iter->next)
	{
		if(ft_strcmp(iter->env_var, iter->next->env_var) > 0)
		{
			swap_nodes(&master->export, iter);
			iter = master->export;
		}
		else
			iter = iter->next;
	}
}

void print_sorted_env(t_minishell *master)
{
	t_env		*iter;
	int			i;
	
	iter = master->export;
	while (iter)
	{
		i = 0;
		ft_putstr_fd("declare -x ", 1);
		while (iter->env_var[i]!= '\0' && iter->env_var[i] != '=')
		{
			ft_putchar_fd(iter->env_var[i], 1);
			i++;
		}
		if (iter->env_var[i] == '=')
		{
			ft_putchar_fd('=', 1);
			i++;
			if (iter->env_var[i] != '\0')
				ft_putchar_fd('"', 1);
			while (iter->env_var[i] != '\0')
			{
				ft_putchar_fd(iter->env_var[i], 1);
				i++;
			}
			ft_putchar_fd('"', 1);
		}
		ft_putchar_fd('\n', 1);
		iter = iter->next;
	}
}