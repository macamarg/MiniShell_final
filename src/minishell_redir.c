/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:27:48 by macamarg          #+#    #+#             */
/*   Updated: 2025/03/24 13:26:20 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	ver todos os redirecionamentos
	abrir tudo que precisa se aberto
	fechar tudo que nao sera usado

*/

/*
	c2r6s1% <case wc -l | wc
	zsh: no such file or directory: case
      0       0       0
		-case doesnt exist but wc (aka cmd2) is executed anyway

	c2r6s1% <b <case wc -l
	zsh: no such file or directory: case
	c2r6s1% <case <b wc -l
	zsh: no such file or directory: case
		-case doesnt exist stop executin of cmd1
*/

static int	handle_heredoc(char **redir_in, int fd)
{
	int	i;

	i = -1;
	while (redir_in[++i])
	{
		if (redir_in[i][0] == 'H')
		{
			if (fd != STDIN_FILENO && fd != -1)
				close(fd);
			fd = redir_heredoc(&redir_in[i][1]);
			if (fd < 0)
				return (-1);
		}
	}
	return (fd);
}

//i = -1; fd = STDIN_FILENO;
static int	handle_infile(char **redir_in, int fd_i, int i, int fd)
{
	while (redir_in[++i])
	{
		if (redir_in[i][0] == 'I')
		{
			if (fd != STDIN_FILENO && fd != -1)
				close(fd);
			fd = check_infile(&redir_in[i][1]);
			if (fd < 0)
				return (-1);
		}
	}
	if (fd_i != STDIN_FILENO && (i - 1) >= 0 && redir_in[i - 1][0] == 'H')
	{
		if (fd != STDIN_FILENO && fd != -1)
			close(fd);
		fd = fd_i;
	}
	if (fd_i != STDIN_FILENO && (i - 1) >= 0 && redir_in[i - 1][0] != 'H')
	{
		if (fd_i != STDIN_FILENO && fd_i != -1)
			close(fd_i);
	}
	return (fd);
}

static int	redir_in(char **redir_in)
{
	int	fd;

	fd = STDIN_FILENO;
	fd = handle_heredoc(redir_in, fd);
	if (fd < 0)
		return (-1);
	fd = handle_infile(redir_in, fd, -1, STDIN_FILENO);
	return (fd);
}

static int	redir_out(char **redir_out, int i)
{
	int	fd;

	fd = STDOUT_FILENO;
	while (redir_out[++i])
	{
		if (i != 0 && fd != STDOUT_FILENO && fd != -1)
			close(fd);
		fd = STDOUT_FILENO;
		if (access(&redir_out[i][1], F_OK) != -1)
		{
			if (access(&redir_out[i][1], W_OK) == -1)
			{
				printf("%s: Permission denied\n", &redir_out[i][1]);
				return (-1);
			}
			if (redir_out[i][0] == 'A')
				fd = (open(&redir_out[i][1], O_WRONLY | O_APPEND));
			else if (redir_out[i][0] == 'W')
				fd = (open(&redir_out[i][1], O_WRONLY | O_TRUNC));
		}
		else
			fd = open(&redir_out[i][1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	return (fd);
}

void	redir_handler(t_minishell *master)
{
	t_command	*iter;
	int			in;
	int			out;

	iter = *master->cmd_lst;
	while (iter)
	{
		if (iter->redir_in)
			iter->fd_in = redir_in(iter->redir_in);
		else
			iter->fd_in = STDIN_FILENO;
		if (iter->redir_out)
			iter->fd_out = redir_out(iter->redir_out, -1);
		else
			iter->fd_out = STDOUT_FILENO;
		if (iter->fd_out < 0)
		{
			ft_putstr_fd("Error opening outfile", 2);
			master->prompt_status = false;
		}
		if (iter->fd_in < 0)
			master->prompt_status = false;
		iter = iter->next;
	}
}
