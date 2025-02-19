/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:10:20 by jrocha-f          #+#    #+#             */
/*   Updated: 2025/01/15 11:20:21 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_order(t_command *cmd_lst)
{
	t_command *current;

	current = cmd_lst;
	while (current != NULL)
	{
		printf("Command: %s, Order: %i, Paths in: %s, Paths out: %s, Fd in: %i, Fd out: %i\n",
		current->cmd[0], current->order, current->redir_in[0],
		current->redir_out[0], current ->fd_in, current->fd_out);
		current = current->next;
	}
}

void	print_cmd_paths(t_command *cmd_lst)
{
	t_command *current;

	current = cmd_lst;
	while (current != NULL)
	{
		printf("Command: %s, Path: %s\n", current->cmd[0], current->cmd_path);
		current = current->next;
	}
}

void	print_paths(char **paths)
{
	int i;

	i = 0;
	while (paths[i] != NULL)
	{
		printf("Path %d: %s\n", i, paths[i]);
		i++;
	}
}

void	print_envp(t_env *envp)
{
	t_env		*iter;

	iter = envp;
	while (iter)
	{
		printf("%s\n", iter->env_var);
		iter = iter->next;
	}
}