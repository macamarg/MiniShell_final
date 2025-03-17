/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_redir_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:06:49 by jrocha-f          #+#    #+#             */
/*   Updated: 2025/03/17 14:11:52 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_infile(char *file)
{
	if (access(file, F_OK) == -1)
	{
		printf("%s: No such infile and directory\n", file);
		return (-1);
	}
	if (access(file, R_OK) == -1)
	{
		printf("%s: Permission denied\n", file);
		return (-1);
	}
	return (open(file, O_RDONLY));
}
