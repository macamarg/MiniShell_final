/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:45:13 by macamarg          #+#    #+#             */
/*   Updated: 2025/03/12 11:57:01 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
		clean all nodes of cmd list
		free list
*/

void	ft_clean_token(t_token **token_lst)
{
	t_token	*iter;
	t_token	*iter2;

	if (*token_lst != NULL && token_lst != NULL)
	{
		iter = *token_lst;
		while (iter != NULL)
		{
			iter2 = iter;
			iter = iter->next;
			free(iter2->token);
			free(iter2);
		}
	}
	if (token_lst)
		free (token_lst);
}

static void	ft_clean_cmdnode(t_command *iter)
{
	if (iter->cmd)
		free_array(iter->cmd);
	if (iter->cmd_path)
		free(iter->cmd_path);
	if (iter->redir_in)
		free_array(iter->redir_in);
	if (iter->redir_out)
		free_array(iter->redir_out);
	if (iter->end_file)
		free_array(iter->end_file);
	if (iter->expand)
		free_array(iter->expand);
}

/*
		clean all nodes of cmd list
		free cmd_lst
*/
void	ft_clean_cmd(t_command **cmd_lst)
{
	t_command	*iter;
	t_command	*iter2;

	if (cmd_lst == NULL || *cmd_lst == NULL)
		return ;
	iter = *cmd_lst;
	while (iter != NULL)
	{
		iter2 = iter;
		ft_clean_cmdnode(iter);
		iter = iter->next;
		free (iter2);
	}
	*cmd_lst = NULL;
	free (cmd_lst);
}
