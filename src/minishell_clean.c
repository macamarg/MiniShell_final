/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_clean.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:01:28 by macamarg          #+#    #+#             */
/*   Updated: 2025/03/03 15:10:39 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
		Close all fds from a list of commands
*/

void	close_cmd_list_fds(t_command *cmd_lst)
{
	t_command	*current;

	current = cmd_lst;
	while (current)
	{
		if (current->fd_in != STDIN_FILENO)
			close(current->fd_in);
		if (current->fd_out != STDOUT_FILENO)
			close(current->fd_out);
		current = current ->next;
	}
}

/*
		clean all nodes of env list
		free env list
*/

void	ft_clean_env(t_env *envp, char **env)
{
	t_env	*iter;
	t_env	*iter2;

	if (envp != NULL)
	{
		iter = envp;
		while (iter != NULL)
		{
			iter2 = iter;
			iter = iter->next;
			free(iter2->env_var);
			free(iter2);
		}
	}
	if (env)
		free_array (env);
}

/*
		ft_clean_cmd(master);
		ft_clean_env(master)
		free master
*/
void	ft_clean_ms(t_minishell *master)
{
	ft_clean_env(master->envp, master->env);
	if (master->prompt)
		ft_clean_env(master->export, NULL);
	if (master->prompt)
		free (master->prompt);
	if (master->cmd_lst)
		ft_clean_cmd(master->cmd_lst);
	if (master->token_lst)
		ft_clean_token(master->token_lst);
}
