/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cpy_envp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:52:08 by macamarg          #+#    #+#             */
/*   Updated: 2025/02/11 11:56:27 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

unsigned int	env_count(t_env *envp)
{
	t_env			*iter;
	unsigned int	count;

	iter = envp;
	count = 0;
	while (iter)
	{
		count++;
		iter = iter->next;
	}
	return(count);
}


char **env_cpy_arr(t_env *envp, int count)
{
	t_env	*iter;
	char	**tmp;
	int		i;

	iter = envp;
	tmp = ft_calloc(count + 1, sizeof(char *));
	i = -1;
	//printf("\ncpy env arr\n");
	while (iter)
	{
		tmp[++i] = ft_strdup(iter->env_var);
		//printf("%s\n", iter->env_var);
		iter = iter->next;
	}
	return (tmp);
}
/* 
int	env_cpy(t_env *master, char **envp)
{
	int	i;
	t_env	*tmp;
	t_env	*iter;
	
	i = -1;
	printf("cpy env to lst\n");
	while (envp[++i])
	{
		tmp = safe_malloc(sizeof(t_env));
		tmp->env_var = ft_strdup(envp[i]);
		//printf("%s\n", tmp->env_var);
		tmp->next = NULL;
		if (master == NULL)
			master = tmp;
		else
		{
			iter = master;
			while (iter->next != NULL)
			{
				iter = iter->next;
			}
			iter->next = tmp;
		}
		//printf("%s\n", master->env_var);
	}
	return (i);
}

int main (int argc, char **argv, char **envp)
{
	t_env	*master;
	char **env_copy;
	int count;
	int i;

	master = NULL;
	printf("teste cpy env\n");
	count = env_cpy(master, envp);
	env_copy = NULL;
	env_copy = env_cpy_arr(master, count);
	printf("%s\n", master->env_var);
	i = -1;
	printf("\nprint cpy env\n");
	while(env_copy[++i])
	{
		printf("\n%i", i);
		printf("env_var[%i] %s\n", i, env_copy[i]);
	}
	
}
 */