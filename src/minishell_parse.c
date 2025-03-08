/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macamarg <macamarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:10:50 by macamarg          #+#    #+#             */
/*   Updated: 2025/03/08 11:12:14 by macamarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	quotes_check(char *prompt)
{
	int	i;

	i = -1;
	if (prompt)
	{
		while (prompt[++i] != '\0')
		{
			if (prompt[i] == '\"')
			{
				while (prompt[++i] != '\0' && prompt[i] != '\"')
					;
				if (prompt[i] == '\0')
					return (false);
			}
			else if (prompt[i] == '\'')
			{
				while (prompt[++i] != '\0' && prompt[i] != '\'')
					;
				if (prompt[i] == '\0')
					return (false);
			}
		}
	}
	return (true);
}

/*
	check if all quotes are closed
	
	check \ (any \ should be syntax error???)
	
	return "syntax error near unexpected token" 
*/
static bool	ft_syntax_check(t_minishell *master)
{
	master->prompt_status = true;
	if (master->prompt)
	{
		if (!quotes_check(master->prompt))
			master->prompt_status = false;
		if (!master->prompt_status)
			printf("syntax error\n");
	}
	return (master->prompt_status);
}

/*
	sintax check

	split line

	token list

	classify and expande token list
	 
*/
void	ft_parseline(t_minishell *master)
{
	if (ft_syntax_check(master))
	{
		master->str_n = 0;
		make_tokenlst(master);
		if (master->prompt_status == true)
			cmd_structfill(master);
	}
}
//free token lst after