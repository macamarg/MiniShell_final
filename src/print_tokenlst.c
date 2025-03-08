/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokenlst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macamarg <macamarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:41:34 by macamarg          #+#    #+#             */
/*   Updated: 2025/03/08 11:29:37 by macamarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_tokenlst(t_token **token_lst)
{
	t_token	*iter;

	iter = *token_lst;
	printf("Current token list:\n");
	while (iter)
	{
		printf("Token: %s %i\n", iter->token, iter->type);
		iter = iter->next;
	}
}

void	print_cmdlst(t_command *cmd_lst)
{
	t_command	*iter_cmd;
	int			i;

	iter_cmd = cmd_lst;

	while (iter_cmd)
	{
		// Print command list
		if (iter_cmd->cmd)
		{
			i = 0; // Start from index 0
			while (iter_cmd->cmd[i])
			{
				printf("cmd %i %s\n", i, iter_cmd->cmd[i]);
				i++;
			}
		}

		// Print redirections (if they exist)
		if (iter_cmd->redir_in)
		{
			i = 0;
			while (iter_cmd->redir_in[i])
			{
				printf("redir_in %i %s\n", i, iter_cmd->redir_in[i]);
				i++;
			}
		}

		if (iter_cmd->redir_out)
		{
			i = 0;
			while (iter_cmd->redir_out[i])
			{
				printf("redir_out %i %s\n", i, iter_cmd->redir_out[i]);
				i++;
			}
		}

		if (iter_cmd->end_file)
		{
			i = 0;
			while (iter_cmd->end_file[i])
			{
				printf("heredoc %i %s\n", i, iter_cmd->end_file[i]);
				i++;
			}
		}

		iter_cmd = iter_cmd->next;
	}
}

void	print_fd(t_minishell *master)
{
	t_command	*iter_cmd;
	int			i;

	iter_cmd = *master->cmd_lst;
	i = 0;
	while (iter_cmd)
	{
		printf("node %i fd in %i\n", ++ i, iter_cmd->fd_in);
		printf("node %i fd out %i\n", i, iter_cmd->fd_out);
		iter_cmd = iter_cmd->next;
	}
}

void	print_env(char **env)
{
	int			i;

	i = -1;
	printf("print env funct\n\n");
	while (env[++i])
	{
		printf("%s\n", env[i]);
	}
}