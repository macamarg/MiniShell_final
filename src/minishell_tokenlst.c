/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tokenlst.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macamarg <macamarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:36:13 by macamarg          #+#    #+#             */
/*   Updated: 2025/03/08 11:28:10 by macamarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	findquotes(char *prompt, int i)
{
	if (prompt[i] == '\"')
	{
		while (prompt[++i] != '\0' && prompt[i] != '\"')
			;
	}
	else if (prompt[i] == '\'')
	{
		while (prompt[++i] != '\0' && prompt[i] != '\'')
			;
	}
	return (i);
}

static int	find_token(char *prompt, int i)
{
	while (prompt[i] != '\0')
	{
		if (prompt[i] == '\'' || prompt[i] == '\"')
			i = findquotes(prompt, i);
		if (prompt[i] != '>' && prompt[i] != '<' && prompt[i] != '|')
		{
			i++;
			if (prompt[i] == '>' || prompt[i] == '<' || prompt[i] == '|'
				|| prompt[i] == ' ')
				return (i);
		}
		else if (prompt[i] == '>' || prompt[i] == '<' || prompt[i] == '|')
		{
			if (prompt[i] == '>' && prompt[i + 1] == '>')
				return (2);
			else if (prompt[i] == '<' && prompt[i + 1] == '<')
				return (2);
			else
				return (1);
		}
	}
	return (i);
}

static void	add_tokenback(t_token **token_lst, t_token *new_token)
{
	t_token	*iter;

	if (*token_lst == NULL)
	{
		*token_lst = new_token;
		return ;
	}
	else
	{
		iter = *token_lst;
		while (iter->next != NULL)
		{
			iter = iter->next;
		}
		iter->next = new_token;
		new_token->prev = iter;
	}
}

static int	new_token(t_minishell *master, char *prompt)
{
	t_token	*tmp;
	int		end;

	end = find_token(prompt, 0);
	tmp = safe_malloc(sizeof(t_token));
	tmp->token = safe_malloc(end + 1);
	ft_strlcpy(tmp->token, prompt, end + 1);
	tmp->next = NULL;
	tmp->next = NULL;
	add_tokenback(master->token_lst, tmp);
	return (end);
}

/*
	memory allocation for token list
	running through prompt to copy token to lst
	check tokens syntax and type
*/
void	make_tokenlst(t_minishell *master)
{
	int		i;

	i = 0;
	master->token_lst = safe_malloc(sizeof(t_token));
	*master->token_lst = NULL;
	while (master->prompt[i] != '\0')
	{
		while (master->prompt[i] == ' ')
			i++;
		i += new_token(master, &master->prompt[i]);
		while (master->prompt[i] == ' ')
			i++;
	}
	class_token(master);
	// if(master->prompt_status == true)
	// 	print_tokenlst(master->token_lst);
}
