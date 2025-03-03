/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_get_path_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:00:11 by jrocha-f          #+#    #+#             */
/*   Updated: 2025/03/03 13:14:54 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_cmdnfound(t_minishell*master, char **cmd)
{
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	master->last_status = 127;
}

char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*dst;
	size_t	len_1;
	size_t	len_2;
	size_t	i;
	size_t	j;

	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	dst = (char *)malloc(len_1 + len_2 + 1);
	if (!dst)
		return (NULL);
	i = -1;
	while (++i < len_1)
		dst[i] = s1[i];
	j = -1;
	while (++j < len_2)
		dst[i + j] = s2[j];
	dst[i + j] = '\0';
	free(s1);
	return (dst);
}
