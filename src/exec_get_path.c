/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_get_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macamarg <macamarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:15:00 by jrocha-f          #+#    #+#             */
/*   Updated: 2025/03/17 17:24:22 by macamarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	while (--i >= 0)
		free(array[i]);
	free (array);
}

static char	**get_paths(t_minishell *master)
{
	int		i;
	char	**paths;

	i = -1;
	paths = NULL;
	while (master->env && master->env[++i] != NULL)
	{
		if (ft_strncmp(master->env[i], "PATH", 4) == 0)
		{
			paths = ft_split((master->env[i] + 5), ':');
			if (!paths)
			{
				perror("malloc error");
				return (NULL);
			}
		}
	}
	return (paths);
}

static char	*absolute_path(char **cmd, t_minishell *master)
{
	char	*path;

	path = NULL;
	if (access(cmd[0], X_OK) == 0)
	{
		path = safe_malloc(ft_strlen(cmd[0]) + 1);
		ft_strlcpy(path, cmd[0], ft_strlen(cmd[0]) + 1);
		return (path);
	}
	perror(cmd[0]);
	master->last_status = 126;
	return (NULL);
}

static char	*not_absolute_path(char **cmd, t_minishell *master)
{
	char	*path_test;
	char	**paths;
	int		i;

	i = -1;
	paths = get_paths(master);
	if (!paths)
	{
		error_cmdnfound(master, cmd);
		return (NULL);
	}
	path_test = check_paths (paths, cmd);
	if (path_test)
		return (path_test);
	else
	{
		error_cmdnfound(master, cmd);
		free_array(paths);
		return (NULL);
	}
}

char	*get_cmdpath(t_minishell *master, t_command *cmd)
{
	char	*path;

	path = NULL;
	if (ft_strchr(cmd->cmd[0], '/') != NULL)
		path = absolute_path(cmd->cmd, master);
	else
		path = not_absolute_path(cmd->cmd, master);
	return (path);
}
