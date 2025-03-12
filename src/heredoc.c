/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:12:30 by jrocha-f          #+#    #+#             */
/*   Updated: 2025/03/12 10:30:28 by jrocha-f         ###   ########.fr       */
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
	free(str);
	str = ft_strdup(new_str);
	free(new_str);
	return (str);
}

static void	free_and_exit(char *line, int fd_pipe)
{
	close(fd_pipe);
	ft_clean_ms(mini_call());
	free(line);
	exit(0);
}

void	here_doc_child(char *eof, int *fd_pipe, bool quotes_flag)
{
	char	*line;
	char	*temp;

	close(fd_pipe[READ_END]);
	line = NULL;
	temp = NULL;
	line = ft_strdup("");
	here_doc_signals_init();
	while (1 && mini_call()->here_status == 0)
	{
		temp = readline("> ");
		if (!temp || ft_strncmp(temp, eof, ft_strlen(eof) + 1) == 0)
		{
			if(temp)
				free(temp);
			break ;
		}
		if (!quotes_flag)
			temp = get_valueexp(temp, mini_call(), -1, 0);
		line = ft_strjoin_free(line, temp);
		line = ft_strjoin_free(line, "\n");
		free(temp);
	}
	free(eof);
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
	printf("new eof: %s\n", new_eof);
	if (ft_strchr(eof, '\"') || ft_strchr(eof, '\''))
		quotes_flag = true;
	if (quotes_flag)
		new_eof = rm_quotes_str(new_eof);
	printf("unquoted: %s\n", new_eof);

	if (pipe(fd_pipe) < 0)
		return (-1);
	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("Fork failed!\n", 2);
		return (-1);
	}
	here_doc_signals_parent();
	if (pid == 0)
		here_doc_child(new_eof, fd_pipe, quotes_flag);
	else
	{
		free (new_eof);
		close (fd_pipe[1]);
		waitpid (pid, NULL, 0);
		return (fd_pipe[READ_END]);
	}
}
