/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:12:30 by jrocha-f          #+#    #+#             */
/*   Updated: 2025/03/04 15:46:01 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static char	*rm_quotes_eof(char *eof)
{
	char	*tmp;
	int		len;
	int		i;

	tmp = NULL;
	len = ft_strlen(eof);
	i = 0;
	tmp = ft_calloc(len + 1, sizeof(char));
	if (tmp == NULL)
		return (NULL);
	while (i < len)
	{
		if (eof[i] == '\'' || eof[i] == '\"')
			i++;
		tmp[i] = eof[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

static void	free_and_exit(char *line, int fd_pipe)
{
	free(line);
	close(fd_pipe);
	exit(0);
}

void	here_doc_child(char *eof, int *fd_pipe, bool quotes_flag)
{
	char	*line;
	char	*temp;

	close(fd_pipe[0]);
	line = NULL;
	temp = NULL;
	line = ft_strdup("");
	while (1)
	{
		temp = readline("> ");
		if (!temp)
			free_and_exit(line, fd_pipe[1]);
		if (ft_strncmp(temp, eof, ft_strlen(eof) + 1) == 0)
		{
			free(temp);
			break ;
		}
		temp = get_valueexp(temp, mini_call(), -1, 0);
		line = ft_strjoin_free(line, temp);
		line = ft_strjoin_free(line, "\n");
		free(temp);
	}
	ft_putstr_fd(line, fd_pipe[1]);
	free_and_exit(line, fd_pipe[1]);
}

int	redir_heredoc(char *eof)
{
	int		fd_pipe[2];
	int		pid;
	bool	quotes_flag;

	//quotes_flag = quotes_check(eof);exit
	if (quotes_flag)
		eof = rm_quotes_eof(eof);
	if (pipe(fd_pipe) < 0)
		return (-1);
	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("Fork failed!\n", 2);
		return (-1);
	}
	if (pid == 0)
		here_doc_child(eof, fd_pipe, quotes_flag);
	else
	{
		close(fd_pipe[1]);
		waitpid(pid, NULL, 0);
		return (fd_pipe[0]);
	}
}
