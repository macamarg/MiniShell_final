/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_classtoken.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macamarg <macamarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:15:32 by macamarg          #+#    #+#             */
/*   Updated: 2025/03/18 13:32:36 by macamarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	exitsyntax_err(void)
{
	t_minishell	*master;

	master = mini_call();
	ft_clean_token(master->token_lst);
	master->prompt_status = false;
	master->token_lst = NULL;
	printf("syntax error\n");
}

static int	class_find(char *token, int i)
{
	if (token[0] == '>' && token[1] == '>')
		return (REDIR_OUTA);
	else if (token[0] == '>')
		return (REDIR_OUTW);
	else if (token[0] == '<' && token[1] == '<')
		return (HEREDOC);
	else if (token[0] == '<')
		return (REDIR_IN);
	else if (token[0] == '|')
		return (PIPE);
	while (token[++i] != '\0')
	{
		if (token[i] == '$')
			return (EXPAND);
	}
	return (STRING);
}

static bool	syntax_pipe(t_token *iter)
{
	bool	stat;

	stat = true;
	if (iter->prev == NULL || iter->next == NULL)
		stat = false;
	else if (iter->next->type == PIPE)
		stat = false;
	else if (iter->next->type == PIPE)
		stat = false;
	if (stat == false)
		exitsyntax_err();
	return (stat);
}

static bool	syntax_redir(t_token *iter)
{
	bool	stat;

	stat = true;
	if (iter->next == NULL)
		stat = false;
	else if (iter->type == HEREDOC && (iter->next->type == STRING
		|| iter->next->type == EXPAND))
		iter->next->type = PATH_IN;
	else if (iter->type == REDIR_IN && iter->next->type == STRING)
		iter->next->type = PATH_IN;
	else if (iter->type == REDIR_OUTA && iter->next->type == STRING)
		iter->next->type = PATH_OUT;
	else if (iter->type == REDIR_OUTW && iter->next->type == STRING)
		iter->next->type = PATH_OUT;
	else if (iter->next->type != STRING)
		stat = false;
	if (stat == false)
		exitsyntax_err();
	return (stat);
}

void	class_token(t_minishell *master)
{
	t_token	*iter;
	bool	token_stat;

	iter = *master->token_lst;
	token_stat = true;
	while (iter)
	{
		iter->type = class_find(iter->token, -1);
		iter = iter->next;
	}
	iter = *master->token_lst;
	while (iter)
	{
		if (iter->type == PIPE)
			token_stat = syntax_pipe(iter);
		else if ((iter->type == REDIR_IN || iter->type == REDIR_OUTW
				|| iter->type == REDIR_OUTA || iter->type == HEREDOC))
			token_stat = syntax_redir(iter);
		if (!token_stat)
			break ;
		iter = iter->next;
	}
}

/*
{
		if (iter->type == PIPE)
		{
			//if (iter->prev == NULL || iter->next == NULL)
			//	exitsyntax_err();	
		}

*/