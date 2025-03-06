#include "../minishell.h"
# include <signal.h>

/*
	struct sigaction:

    sa_handler: The function pointer to the signal handler.

    sa_mask: A set of signals to block while the handler is running.

    sa_flags: Flags to modify the behavior of the signal handler.
	
	SIG_IGN to ignore this signal CTRL-C
*/

void	prompt_signals_init(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sa_int.sa_handler = sigint_handler;
	sigaddset(&sa_int.sa_mask, SIGINT);
	//if SIGINT(CTRL-C) calls sigint_handler
	sigaction(SIGINT, &sa_int, 0);
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sa_quit.sa_handler = SIG_IGN;
	sigaddset(&sa_quit.sa_mask, SIGQUIT);
	//if SIGQUIT(CTRL-\) calls SIG_IGN
	sigaction(SIGQUIT, &sa_quit, 0);
}

void	here_doc_signals_init(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	//if SIGINT(CTRL-C) calls here_handler
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sa_int.sa_handler = here_handler;
	sigaddset(&sa_int.sa_mask, SIGINT);
	sigaction(SIGINT, &sa_int, 0);
	sigemptyset(&sa_quit.sa_mask);
	//if SIGQUIT(CTRL-\) calls SIG_IGN and restore std-behav
	sa_quit.sa_flags = SA_RESTART;
	sa_quit.sa_handler = SIG_IGN;
	sigaddset(&sa_quit.sa_mask, SIGQUIT);
	sigaction(SIGQUIT, &sa_quit, 0);

}


/*

	A child created via fork(2) inherits a copy of its parent's signal dis‐
    positions.   During  an  execve(2), the dispositions of handled signals
    are reset to the default (sa_int.sa_flags = SA_RESTART;); 
	the dispositions of ignored signals are  left unchanged.

*/
void	child_signals_init(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	//if SIGINT calls child_handler and restart signal behav
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sa_int.sa_handler = child_handler;
	sigaddset(&sa_int.sa_mask, SIGINT);
	sigaction(SIGINT, &sa_int, 0);
	//if SIGQUIT calls child_handler and restore signal behav
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sa_quit.sa_handler = child_handler;
	sigaddset(&sa_quit.sa_mask, SIGQUIT);
	sigaction(SIGQUIT, &sa_quit, 0);

}

//after acquire prompt until execute command
void	ignore_signals_init(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	//if SIGINT(CTRL-C) calls SIG_IGN
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sa_int.sa_handler = SIG_IGN;
	sigaddset(&sa_int.sa_mask, SIGINT);
	sigaction(SIGINT, &sa_int, 0);
	//if SIGQUIT(CTRL-\) calls SIG_IGN
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sa_quit.sa_handler = SIG_IGN;
	sigaddset(&sa_quit.sa_mask, SIGQUIT);
	sigaction(SIGQUIT, &sa_quit, 0);
}
