/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:12:30 by jrocha-f          #+#    #+#             */
/*   Updated: 2025/03/05 16:57:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			{
				new_str[j++] = str[i++];
			}
			i++;
		}
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	str = ft_strdup(new_str);
	free(new_str);
	return (str);
}

static void	free_and_exit(char *line, int fd_pipe)
{
	ft_clean_ms(mini_call());
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
		if (!quotes_flag)
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

	quotes_flag = false;
	if (ft_strchr(eof, '\"') || ft_strchr(eof, '\''))
		quotes_flag = true;
	if (quotes_flag)
		eof = rm_quotes_str(eof);
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
