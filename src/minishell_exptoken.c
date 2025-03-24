/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exptoken.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:08:12 by macamarg          #+#    #+#             */
/*   Updated: 2025/03/24 10:36:32 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	wordcount(char *token)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (token[i] != '\0')
	{
		while (token[i] == ' ')
			i++;
		while (token[i] != ' ' && token[i] != '\0')
			i++;
		count++;
		while (token[i] == ' ')
			i++;
	}
	return (count);
}

static void	new_expandtoken(char *str, t_token *token_lst)
{
	int		len;
	t_token	*tmp_token;

	len = ft_strlen(str);
	tmp_token = safe_malloc(sizeof(t_token));
	tmp_token->token = safe_malloc(len + 1);
	ft_memcpy(tmp_token->token, str, len);
	tmp_token->token[len] = '\0';
	tmp_token->type = STRING;
	if (token_lst->next != NULL)
		token_lst->next->prev = tmp_token;
	token_lst->next = tmp_token;
	tmp_token->next = token_lst->next;
	tmp_token->prev = token_lst->prev;
}

static void	insert_exp(char	**splited, t_token *token_lst,
t_token *next_token, int count)
{
	t_token	*iter;
	int		i;
	int		len;

	i = 0;
	if (token_lst->token)
		free(token_lst->token);
	token_lst->token = NULL;
	len = ft_strlen(splited[0]);
	token_lst->token = safe_malloc(len + 1);
	ft_memcpy(token_lst->token, splited[0], len);
	token_lst->token[len] = '\0';
	iter = token_lst;
	while (++i < count)
	{
		new_expandtoken(splited[i], iter);
		iter = iter->next;
	}
	iter->next = next_token;
	if (next_token != NULL)
		next_token->prev = iter;
}

static bool	only_expand(char *token)
{
	int		i;

	i = 0;
	if (token[0] == '"')
		return (true);
	while (token[i] != '\0')
	{
		if (ft_isalnum(token[i]) == 1 || token[i] == '_' || token[i] == '$')
			i++;
		else
			return (true);
	}
	return (false);
}

void	token_expansion(t_token *token_lst)
{
	char	**splited;
	int		i;
	bool	quotes;

	splited = NULL;
	quotes = false;
	if (token_lst->prev && token_lst->prev->type == HEREDOC)
		return ;
	if (only_expand(token_lst->token))
		quotes = true;
	token_lst->token = get_valueexp(token_lst->token, mini_call(), -1, 0);
	i = wordcount(token_lst->token);
	if (!quotes && i > 1)
	{
		splited = ft_split(token_lst->token, ' ');
		insert_exp(splited, token_lst, token_lst->next, i);
		i = 0;
		while (splited [i] != NULL)
			free(splited[i++]);
		free(splited);
	}
}
