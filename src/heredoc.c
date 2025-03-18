/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:12:30 by jrocha-f          #+#    #+#             */
/*   Updated: 2025/03/18 15:04:17 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	hd_parent_cleanup(char *new_eof, int fd, int pid)
{
	free (new_eof);
	close (fd);
	waitpid (pid, NULL, 0);
}

char	*rm_quotes_str(char *str)
{
	int		i;
	int		j;
	int		end;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = NULL;
	new_str = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			end = findquotes(str, i);
			i++;
			while (i < end)
				new_str[j++] = str[i++];
			i++;
		}
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

static void	free_and_exit(char *line, int fd_pipe)
{
	close(fd_pipe);
	close_cmd_list_fds(mini_call()->cmd_lst);
	ft_clean_ms(mini_call());
	free(line);
	exit(EXIT_SUCCESS);
}

void	here_doc_child(char *eof, int *fd_pipe, bool quotes_flag)
{
	char	*line;
	char	*temp;

	close(fd_pipe[READ_END]);
	temp = NULL;
	line = ft_strdup("");
	here_doc_signals_init();
	while (1 && mini_call()->here_status == 0)
	{
		temp = readline("> ");
		if (!temp || ft_strncmp(temp, eof, ft_strlen(eof) + 1) == 0)
		{
			if (temp)
				free(temp);
			break ;
		}
		if (!quotes_flag)
			temp = get_valueexp(temp, mini_call(), -1, 0);
		line = heredoc_join(line, temp);
		free(temp);
	}
	free(eof);
	if (mini_call()->here_status == 0)
		ft_putstr_fd(line, fd_pipe[WRITE_END]);
	free_and_exit(line, fd_pipe[WRITE_END]);
}

int	redir_heredoc(char *eof)
{
	int		fd_pipe[2];
	int		pid;
	bool	quotes_flag;
	char	*new_eof;

	quotes_flag = false;
	new_eof = ft_strdup(eof);
	if (ft_strchr(eof, '\"') || ft_strchr(eof, '\''))
		quotes_flag = true;
	new_eof = rm_quotes_str(new_eof);
	if (!new_eof)
		return (heredoc_error("Memory allocation failed", new_eof));
	if (pipe(fd_pipe) < 0)
		return (-1);
	pid = fork();
	if (pid < 0)
		return (heredoc_error("Fork failled", new_eof));
	here_doc_signals_parent();
	if (pid == 0)
		here_doc_child(new_eof, fd_pipe, quotes_flag);
	else
		hd_parent_cleanup(new_eof, fd_pipe[1], pid);
	return (fd_pipe[READ_END]);
}
