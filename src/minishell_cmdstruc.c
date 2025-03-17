/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cmdstruc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:33:09 by macamarg          #+#    #+#             */
/*   Updated: 2025/03/17 15:54:28 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	identificar clusters de comandos
		contar numero de cmd + args e copiar para **cmd
		contar redir_in copiar para **redir_in
		contar redir_out copiar para **redir_out
*/

static void	cmd_init(t_command *tmp)
{
	tmp->prev = NULL;
	tmp->next = NULL;
	tmp->type = -1;
	tmp->cmd = NULL;
	tmp->cmd_path = NULL;
	tmp->redir_in = NULL;
	tmp->redir_out = NULL;
	tmp->end_file = NULL;
	tmp->expand = NULL;
	tmp->pipe = false;
	tmp->order = -1;
	tmp->fd_in = STDIN_FILENO;
	tmp->fd_out = STDOUT_FILENO;
}

static void	token_count(t_token **token_lst, t_count *cmd_count)
{
	t_token	*iter;
	bool	quotes;

	iter = *token_lst;
	while (iter && iter->type != PIPE)
	{
		iter->token = quotes_rm(iter);
		if (iter->type == EXPAND || iter->type == STRING)
		{
			token_expansion(iter);
			if (iter->token != NULL)
				iter->type = STRING;
		}
		if (iter->type == STRING)
			cmd_count->cmd_n++;
		else if (iter->type == PATH_IN)
			cmd_count->redirin_n++;
		else if (iter->type == PATH_OUT)
			cmd_count->redirout_n++;
		iter = iter->next;
	}
	if (iter && iter->type == PIPE)
		cmd_count->pipe++;
}

static void	count_init(t_count *cmd_count)
{
	cmd_count->cmd_n = 0;
	cmd_count->redirin_n = 0;
	cmd_count->redirout_n = 0;
	cmd_count->heredoc_n = 0;
	cmd_count->pipe = 0;
}

static void	new_cmd(t_minishell *master, t_token **token_lst,
	t_count *cmd_count)
{
	t_command	*tmp;
	t_command	*iter;

	tmp = NULL;
	tmp = safe_malloc(sizeof(t_command));
	cmd_init(tmp);
	tmp->cmd = cmd_fill(token_lst, cmd_count->cmd_n, STRING);
	tmp->redir_in = cmd_fill(token_lst, cmd_count->redirin_n, PATH_IN);
	tmp->redir_out = cmd_fill(token_lst, cmd_count->redirout_n, PATH_OUT);
	if (cmd_count->pipe == 1)
		tmp->pipe = true;
	if (*master->cmd_lst == NULL)
		*master->cmd_lst = tmp;
	else
	{
		iter = *master->cmd_lst;
		while (iter->next != NULL)
		{
			iter = iter->next;
		}
		iter->next = tmp;
		tmp->prev = iter;
	}
}

void	cmd_structfill(t_minishell *master)
{
	t_token		*iter;
	t_command	*iter_cmd;
	t_count		cmd_count;

	iter = *master->token_lst;
	master->cmd_lst = safe_malloc(sizeof(t_command));
	*master->cmd_lst = NULL;
	master->cmd_status == true;
	while (iter)
	{
		count_init(&cmd_count);
		iter->token = quotes_rm(iter);
		token_count(&iter, &cmd_count);
		new_cmd(master, &iter, &cmd_count);
		while (iter && iter->type != PIPE)
			iter = iter->next;
		if (iter && iter->type == PIPE)
			iter = iter->next;
	}
	redir_handler(master);
}
/*


typedef enum e_class
{
	STRING,//
	REDIR_IN,//
	REDIR_OUT,//Token lll type 0
Token llll type 0
Token llll type 0
filling cmd struct
new cmd teste
lll
llll
llll
cmd 0 (null)
cmd 1 llll
cmd 2 llll
	PATH,//
	PIPE,//
	EXPAND,
	HEREDOC,
	ENDFILE,
}	t_class;

*/

// iter_cmd = *master->cmd_lst;
	// int i;
	// while (iter_cmd)
	// {
	// 	i = 0;
	// 	printf("\n");
	// 	while(iter_cmd->cmd[++i] != NULL)
	// 		printf("cmd %s\n", iter_cmd->cmd[0]);
	// 	// i = -1;
	// 	// printf("redir_in\n");
	// 	// while(iter_cmd->redir_in[++i])
	// 	// 	printf("redir_in %s\n", iter_cmd->redir_in[i]);
	// 	// i = -1;
	// 	// printf("redir_outa\n");
	// 	// while(iter_cmd->redir_outa[++i])
	// 	// 	printf("redir_outa %s\n", iter_cmd->redir_outa[i]);
	// 	// i = -1;
	// 	// printf("redir_outw\n");
	// 	// while(iter_cmd->redir_outw[++i])
	// 	// 	printf("redir_outw %s\n", iter_cmd->redir_outw[i]);
	// 	iter_cmd = iter_cmd->next;
	// }