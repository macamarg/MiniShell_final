/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expandutils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macamarg <macamarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 10:45:55 by macamarg          #+#    #+#             */
/*   Updated: 2025/03/17 10:07:25 by macamarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	if_copy(char *token, int k, int j, int i)
{
	int	p;
	int	q;

	p = -1;
	if (token[j + k] != '"' && token[j + k] != '\'')
		return (true);
	while (token[++p] != '\0')
	{
		if (token[p] == '"' || token[p] == '\'')
		{
			q = p;
			p = findquotes(token, p);
			if (token[q] != token[j + k] && (q < (j + k) && (j + k) < p))
				return (true);
			else if (p == (j + k) || q == (j + k))
				return (false);
		}
	}
	return (false);
}

char	*collectprior(char *token, int i, int j)
{
	char	*dest;
	int		d;
	int		t;

	dest = NULL;
	dest = safe_malloc(i - j + 1);
	d = 0;
	t = 0;
	while ((d + t) < (i - j))
	{
		if (if_copy(token, d + t, j, i))
		{
			((unsigned char *)dest)[d] = ((unsigned char *)token)[j + t + d];
			d++;
		}
		else
			t++;
	}
	dest[d] = '\0';
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

bool	when_expand(char *token, int i)
{
	int		j;

	j = -1;
	while (token[++j] != '\0')
	{
		if (token[j] == '"')
		{
			while (token[++j] != '\0' && token[j] != '"')
				;
			if (j > i)
				return (true);
		}
		if (token[j] == '\'')
		{
			while (token[++j] != '\0' && token[j] != '\'')
				;
			if (j > i)
				return (false);
		}
		if (j >= i)
			break ;
	}
	return (true);
}

bool	when_cpy(char *token, int i, int j)
{
	int		q;

	q = 0;
	while (token[q + j] == '"')
		q++;
	if ((q + j) == i)
		return (false);
	q = 0;
	while (token[q + j] == '\'')
		q++;
	if ((q + j) == i)
		return (false);
	return (true);
}
