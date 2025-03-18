/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macamarg <macamarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:02:38 by marvin            #+#    #+#             */
/*   Updated: 2025/03/18 13:11:03 by macamarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
 * Change the current directory to the specified directory.
 * If no directory is specified, change to the user's home directory.
 * If the directory does not exist, display an error message.
 * If the directory is not accessible, display an error message.

	int chdir(const char *path);
	changes the current working directory of the calling
		process to the directory specified in path.
	On success, zero is returned.  On error, -1 is returned, and
		errno is set to indicate the error.
 */

static void	change_env_vars(char *old_path, t_minishell *master)
{
	char	*env_new_path;
	char	*env_old_path;

	get_local_directory(master);
	env_new_path = ft_strjoin("PWD=", master->local_dir);
	ft_execute_export(env_new_path, master);
	env_old_path = ft_strjoin("OLDPWD=", old_path);
	ft_execute_export(env_old_path, master);
	free(env_new_path);
	free(env_old_path);
}

static char	*find_home(t_minishell *master)
{
	int		i;
	char	*path;

	i = -1;
	path = NULL;
	while (master->env && master->env[++i])
	{
		if (ft_strlen(master->env[i]) > 5
			&& ft_strncmp(master->env[i], "HOME=", 5) == 0)
		{
			path = ft_strdup(master->env[i] + 5);
			break ;
		}
	}
	return (path);
}

static int	cd_home(t_minishell *master)
{
	char	*path;

	path = find_home(master);
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

static int	check_cd_errors(t_command *cmd, t_minishell *master)
{
	if (!master || !master->env)
	{
		ft_putstr_fd("cd: environment not set\n", 2);
		return (1);
	}
	if (cmd->cmd[1] && cmd->cmd[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	return (0);
}

int	ft_cd(t_command *cmd, t_minishell *master)
{
	char	*path;
	char	*old_path;

	path = NULL;
	if (check_cd_errors(cmd, master) == 1)
		return (1);
	if (cmd->cmd[1] == NULL)
	{
		cd_home(master);
		return (master->last_status);
	}
	path = ft_strdup(cmd->cmd[1]);
	if (!path)
		return (1);
	if (chdir(path) == -1)
	{
		ft_error_cd(path);
		return (1);
	}
	old_path = ft_strdup(master->local_dir);
	change_env_vars(old_path, master);
	free(old_path);
	free(path);
	return (0);
}
