/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:02:38 by marvin            #+#    #+#             */
/*   Updated: 2025/01/22 15:02:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
 * Change the current directory to the specified directory.
 * If no directory is specified, change to the user's home directory.
 * If the directory does not exist, display an error message.
 * If the directory is not accessible, display an error message.
 * If the directory is not a directory, display an error message.
 * If the directory is not readable, display an error message.
 * If the directory is not writable, display an error message.
 * If the directory is not executable, display an error message.

    int chdir(const char *path);
	changes the current working directory of the calling
       process to the directory specified in path.
	On success, zero is returned.  On error, -1 is returned, and
       errno is set to indicate the error.
 */

static int cd_home(t_minishell *master)
{
	int i;
	char *path;

	i = -1;
	path = NULL;
	while (master->env[++i])
	{
		if (ft_strncmp(master->env[i], "HOME=", 5) == 0 && ft_strlen(master->env[i]) > 5)
		{
			path = ft_strdup(master->env[i] + 5);
			break ;
		}
	}
	if (!path)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		master->last_status = 1;
		return (1);
	}
	if (chdir(path) == -1)
	{
		perror("cd");
		master->last_status = 1;
	}
	free(path);
	return (master->last_status);
}

int	ft_cd(t_command *cmd, t_minishell *master)
{
	char	*path;
	int		i;

	path = NULL;
	i = 0;
	if (!master || !master->env)
	{
		ft_putstr_fd("cd: environment not set\n", 2);
		master->last_status = 1;
		return (1);
	}
	if (cmd->cmd[1] == NULL)
	{
		cd_home(master);
		return (master->last_status);
	}
	if (cmd->cmd[1] && cmd->cmd[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		master->last_status = 1;
		return (1);
	}
	path = ft_strdup(cmd->cmd[1]);
	if (!path)
		return (1);
	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		perror(path);
		master->last_status = 1;
	}
	free(path);
	return (master->last_status);
}
