/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macamarg <macamarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:53:36 by jrocha-f          #+#    #+#             */
/*   Updated: 2025/03/18 13:23:03 by macamarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	heredoc_error(char *msg, char *new_eof)
{
	ft_putstr_fd(msg, 2);
	if (new_eof)
		free (new_eof);
	return (-1);
}

char	*heredoc_join(char *line, char *temp)
{
	line = ft_strjoin_free(line, temp);
	line = ft_strjoin_free(line, "\n");
	return (line);
}
