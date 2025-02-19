/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishells_parse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macamarg <macamarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:10:50 by macamarg          #+#    #+#             */
/*   Updated: 2024/12/04 11:31:49 by macamarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	quotes_check(char *prompt)
{
	int	i;
	int	dquotes_n;
	int	squotes_n;

	i = -1;
	dquotes_n = 0;
	squotes_n = 0;
	if(prompt)
	{
		while (prompt[++i] != '\0')
		{
			if (prompt[i] == '\"')
				dquotes_n++;
			else if (prompt[i] == '\'')
				squotes_n++;
		}
	}
	if (dquotes_n % 2 == 0 && squotes_n % 2 == 0)
		return (true);
	else
		return (false);
}

static bool	special_char(char *prompt)
{
	int	i;

	i = -1;
	if(prompt)
	{
		while (prompt[++i] != '\0')
		{
			if (prompt[i] == '\\' || prompt[i] == ';')
				return (false);
		}
	}
	return (true);
}

/*
	check if all quotes are closed

	check \ (any \ should be syntax error???)

	return "syntax error near unexpected token"
		preciso do split??
*/
bool	ft_syntax_check(t_minishell *master)
{
	int	i;
	int	d_quotes;

	i = 0;
	master->prompt_status = true;
	if (master->prompt)
	{
		if (!quotes_check(master->prompt))
			master->prompt_status = false;
		if(!special_char(master->prompt))
			master->prompt_status = false;
		if (!master->prompt_status)
			printf("syntax error near unexpected token\n");
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
		//split prompt
		master->cmd_split = ft_split(master->prompt, ' ');

		int	i;

		i = 0;
		while (master->cmd_split[i])
		{
			//printf("%s\n", master->cmd_split[i]);
			free (master->cmd_split[i]);
			i++;
		}
		free(master->cmd_split);
		//lst
		//classify
	}
}