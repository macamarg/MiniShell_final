/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cmd_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macamarg <macamarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:24:01 by macamarg          #+#    #+#             */
/*   Updated: 2025/01/15 14:44:50 by macamarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*quotes_rm(t_token *iter)
{
	char	*tmp;

	tmp = NULL;
	if(iter->type == STRING && iter->token[0] == '\'')
	{
		tmp = ft_strtrim(iter->token, "\'");
		free(iter->token);
	}
	else if(iter->type == STRING && iter->token[0] == '\"')
	{
		tmp = ft_strtrim(iter->token, "\"");
		free(iter->token);
	}
	else
		return(iter->token);	
	return(tmp);
}