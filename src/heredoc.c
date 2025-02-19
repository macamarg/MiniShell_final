/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:12:30 by jrocha-f          #+#    #+#             */
/*   Updated: 2025/02/19 09:38:42 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	here_doc_child(char *eof, int *fd_pipe)
{
	char	*line;
	char	*new_line;
	char	*temp;

	close(fd_pipe[0]);
	line = NULL;
	temp = NULL;
	line = ft_strdup("");
	while(1)
	{
		temp = readline("> ");
		if(!temp)
		{
			free(line);
			close(fd_pipe[1]);
			exit(0);
		}
		if (ft_strncmp(temp, eof, ft_strlen(eof)) == 0)  // Stop if EOF is matched
		{
			free(temp);
			break;
		}
		new_line = ft_strjoin(line, temp);
		free(line);
		line = ft_strjoin(new_line, "\n");  // Add newline
		free(new_line);
		free(temp);
	}
	ft_putstr_fd(line, fd_pipe[1]);  // Write full input to pipe
	free(line);
	close(fd_pipe[1]);
	exit(0);
}

int	redir_heredoc(char *eof)
{
	int		fd_pipe[2];
	int		pid;

	if (pipe(fd_pipe) < 0)
		return(-1);
	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("Fork failed!\n", 2);
		return(-1);
	}
	if (pid == 0) /*child*/
		here_doc_child(eof, fd_pipe);
	else /*parent*/
	{
		close(fd_pipe[1]);
		waitpid(pid, NULL, 0);
		return(fd_pipe[0]);
	}
}