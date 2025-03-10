/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signhadle.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macamarg <macamarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:26:12 by macamarg          #+#    #+#             */
/*   Updated: 2025/03/10 17:07:23 by macamarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int signum)
{
	t_minishell	*master;

	master = mini_call();
	if (signum == SIGINT)
	{
		master->last_status = 130;
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

//if CTRL-C status change and then close STDIN and back to prompt
//if CTRL-D //if CTRL-C status change and then close STDIN and back to prompt
void	here_handler(int signum)
{
	t_minishell	*master;

	master = mini_call();
	if (signum == SIGINT)
	{
		master->last_status = 130;
		master->here_status = 130;
		ft_putchar_fd('\n', 1);
		close(STDIN_FILENO);
	}
}

void	hereparent_handler(int signum)
{
	t_minishell	*master;

	master = mini_call();
	if (signum == SIGINT)
	{
		master->last_status = 130;
		master->here_status = 130;
	}
	if (signum == SIGQUIT)
		master->last_status = 131;
}


//status change and then child/exec will handle signal acordingly
void	child_handler(int signum)
{
	t_minishell	*master;

	master = mini_call();
	if (signum == SIGINT)
		master->last_status = 130;
	if (signum == SIGQUIT)
		master->last_status = 131;
}
//change minishell.status para g_status