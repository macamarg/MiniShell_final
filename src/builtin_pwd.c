/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:02:52 by jrocha-f          #+#    #+#             */
/*   Updated: 2025/03/03 11:19:22 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	pwd_builtin:
	Executes the builtin pwd command and displays the current working 
	directory path.
	Returns 0 if successful, 1 if an error occured.

	Uses size as the initial buffer size (unless it is indeterminate or very
	large), and calls getcwd() with progressively larger buffers until it does
	not give an [ERANGE] error.

	TODO: Check possible errors without environment
*/

static void	error_getcwd(t_minishell *master)
{
	master->local_dir = NULL;
	perror("error getcwd");
	master->last_status = EXIT_FAILURE;
	return ;
}

void	get_local_directory(t_minishell *master)
{
	size_t	size;
	char	*buff;
	int		error;

	size = 100;
	buff = NULL;
	error = ERANGE;
	buff = safe_malloc(sizeof(char) * size);
	while (error == ERANGE)
	{
		buff = getcwd(buff, sizeof(char) * size);
		if (buff)
			break ;
		if (errno != ERANGE)
			error_getcwd(master);
		size *= 2;
		free (buff);
		buff = NULL;
		buff = safe_malloc(sizeof(char) * size);
	}
	master->local_dir = buff;
}

int	ft_pwd(t_command *cmd, t_minishell *master)
{
	ft_putendl_fd(master->local_dir, cmd->fd_out);
	return (0);
}
