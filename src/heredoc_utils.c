/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:53:36 by jrocha-f          #+#    #+#             */
/*   Updated: 2025/03/17 16:23:26 by jrocha-f         ###   ########.fr       */
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
