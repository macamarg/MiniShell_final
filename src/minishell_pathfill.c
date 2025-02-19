/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pathfill.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:23:20 by macamarg          #+#    #+#             */
/*   Updated: 2025/02/12 14:59:48 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*pathin_fill(char *token, int flag)
{
	char *collect;

	collect = NULL;
	if (flag == REDIR_IN)
		collect = ft_strjoin("I", token);
	if (flag == HEREDOC)
		collect = ft_strjoin("H", token);
	return (collect);
}

static char	*pathout_fill(char *token, int flag)
{
	char *collect;

	collect = NULL;
	if (flag == REDIR_OUTA)
		collect = ft_strjoin("A", token);
	if (flag == REDIR_OUTW)
		collect = ft_strjoin("W", token);
	return (collect);
}

char	**cmd_fill(t_token **token_lst, int count, int t_class)
{
	t_token	*iter;
	char	**collect;
	int		i;

	iter = *token_lst;
	collect = NULL;
	collect = ft_calloc(count + 1, sizeof(char *));
	if (!collect)
		return NULL; 
	i = 0;
	while (iter && iter->type != PIPE)
	{
		if (iter->type == t_class && t_class != PATH_IN && t_class != PATH_OUT)
			collect[i++] = ft_strdup(iter->token);
		else if (iter->type == PATH_IN && t_class == PATH_IN)
			collect[i++] = pathin_fill(iter->token, iter->prev->type);
		else if (iter->type == PATH_OUT && t_class == PATH_OUT)
			collect[i++] = pathout_fill(iter->token, iter->prev->type);
		iter = iter->next;
	}
	if (i == 0)  // If collect is empty, free it and return NULL
	{
		free(collect);
		return NULL;
	}
	return (collect);
}
