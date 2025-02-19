/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:08:25 by macamarg          #+#    #+#             */
/*   Updated: 2025/02/06 13:36:44 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	env_cpy(t_minishell *master, char **envp)
{
	int	i;
	t_env	*tmp;
	t_env	*iter;

	i = -1;
	while (envp[++i])
	{
		tmp = safe_malloc(sizeof(t_env));
		tmp->env_var = ft_strdup(envp[i]);
		tmp->next = NULL;
		if (master->envp == NULL)
			master->envp = tmp;
		else
		{
			iter = master->envp;
			while (iter->next != NULL)
			{
				iter = iter->next;
			}
			iter->next = tmp;
		}
	}
	master->env = env_cpy_arr(master->envp, i);
}

//initi t_minishell
t_minishell	*mini_init(char **argv, char **envp)
{
	t_minishell	*master;

	master = mini_call();
	master->envp = NULL;

	env_cpy(master, envp);
	master->export = NULL;
	sort_env(master, master->env);
	master->argv = argv;
	//print_env(master->env);
	master->last_status = 0;
	return (master);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*master;

	if (argc == 1)
	{
		master = mini_init(argv, envp);
		ft_getprompt(master);
		//ft_clean_ms(master);
	}
	else
	{
		printf("bash: %s: No such file or directory", argv[1]);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
