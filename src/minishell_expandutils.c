/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expandutils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macamarg <macamarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 10:45:55 by macamarg          #+#    #+#             */
/*   Updated: 2025/03/08 11:07:05 by macamarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*collectprior(char *token, int i, int j)
{
	char	*dest;

	dest = NULL;
	dest = safe_malloc(i - j + 1);
	ft_memcpy(dest, &token[j], i - j);
	dest[i - j] = '\0';
	return (dest);
}

//i = 0;
char	*std_exp(char *tmp, t_minishell *master, int i)
{
	char		*value;
	char		*tmp2;
	t_env		*iter;

	iter = master->envp;
	value = NULL;
	while (ft_isalnum(tmp[i]) == 1 || tmp[i] == '_')
		i++;
	if (i > 0)
	{
		tmp2 = safe_malloc(i + 2);
		ft_memcpy(tmp2, tmp, i);
		tmp2[i] = '=';
		tmp2[i + 1] = '\0';
		while (iter && value == NULL)
		{
			if (ft_strncmp(iter->env_var, tmp2, ft_strlen(tmp2)) == 0)
				value = ft_strdup(&(iter->env_var[ft_strlen(tmp2)]));
			else
				iter = iter->next;
		}
		free (tmp2);
	}
	return (value);
}
