#include "../minishell.h"

void	sigint_handler(int signum)
{
	t_minishell	*master;

	master = mini_call();
	if (signum == SIGINT)
	{
		master->last_status = 130;
		ft_putchar_fd('\n', 1); // Print a newline
		//re-prompt the user
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
//if CTRL-C status change and then close STDIN and back to prompt 
void	here_handler(int signum)
{
	t_minishell	*master;

	master = mini_call();
	if (signum == SIGINT)
	{
		master->last_status = 130;
		ft_putchar_fd('\n', 1);
		close(STDIN_FILENO);
	}
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