/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_readline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macamarg <macamarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:46:44 by macamarg          #+#    #+#             */
/*   Updated: 2025/03/17 17:51:16 by macamarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

/*
	get prompt
	callparse

	call exec
*/

void	ft_getprompt(t_minishell *master)
{
	while (1)
	{
		prompt_signals_init();
		master->prompt = readline("shell> ");
		if (!master->prompt)
			master->prompt = ft_strdup("exit");
		if (master->prompt && *master->prompt)
		{
			add_history(master->prompt);
			ft_parseline(master);
			if (master->prompt_status == true)
				mini_exec(master);
			if (master->token_lst && *master->token_lst)
				ft_clean_token(master->token_lst);
			master->token_lst = NULL;
			if (master->cmd_lst && *master->cmd_lst)
				close_cmd_list_fds(master->cmd_lst);
			if (master->cmd_lst && *master->cmd_lst)
				ft_clean_cmd(master->cmd_lst);
			master->cmd_lst = NULL;
		}
		free (master->prompt);
		master->prompt = NULL;
	}
}
/*
int main(void)
{
	t_minishell	*master;

	master = malloc(sizeof(t_command));
	ft_getprompt(master);
	return (0);
} */

//-lreadline
