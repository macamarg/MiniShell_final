/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macamarg <macamarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:21:56 by macamarg          #+#    #+#             */
/*   Updated: 2025/03/08 10:55:04 by macamarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	len_count(char *tmp)
{
	int	i;

	i = 0;
	//if (tmp[i] == '?')
	//echo "$$HOME$USER" = /home/mcmarqsmcmarqs
	if (tmp[i] == '?' || tmp[i] == '$')
		i++;
	else
	{
		while (tmp[i] != '\0' && (ft_isalnum(tmp[i]) == 1 || tmp[i] == '_'))
			i++;
		if (tmp[i] == '"')
			i++;
	}
	return (i);
}

//i = 0; j = 0;
static int	exp_count(char *tmp, int i, int j)
{
	int	n;

	n = 0;
	while (tmp[i] != '\0')
	{
		if (tmp[i] == '$')
		{
			if (j != i)
				n++;
			i++;
			i += len_count(&tmp[i]);
			j = i;
			n++;
		}
		else
			i++;
	}
	if (j != i)
		n++;
	return (n);
}

//collect = collectexp(n, tmp, master, 0, 0);
static char	**collectexp(char *token, t_minishell *master, int i, int j)
{
	int		k;
	char	**collect;	

	k = -1;
	collect = NULL;
	collect = (char **)ft_calloc(exp_count(token, 0, 0), sizeof(char *));
	while (token[i] != '\0')
	{
		if (token[i] == '$' && token[i + 1] != '\0' && when_expand(token, i) == true)
		{
			if (j != i && when_cpy(token, i, j))
				collect[++k] = collectprior(token, i, j);
			if (token[++i] == '?')
				collect[++k] = ft_itoa(master->last_status);
			else
				collect[++k] = std_exp(&token[i], master, 0);
			i += len_count(&token[i]);
			j = i;
		}
		else
			i++;
	}
	if (j != i && when_cpy(token, i, j))
		collect[++k] = collectprior(token, i, j);
	return (collect);
}

static char	*expjoin(int n, char **collect)
{
	int		i;
	int		j;
	int		len;
	char	*dest;

	i = -1;
	len = 0;
	while (++i < n)
	{
		if (collect[i] != NULL)
			len += ft_strlen(collect[i]);
	}
	i = -1;
	j = 0;
	dest = safe_malloc(len + 1);
	while (++i < n)
	{
		if (collect[i] != NULL)
		{
			ft_memcpy(&dest[j], collect[i], ft_strlen(collect[i]));
			j += ft_strlen(collect[i]);
		}
	}
	dest[len] = '\0';
	return (dest);
}

//i = -1 n = 0
char	*get_valueexp(char *token, t_minishell *master, int i, int n)
{
	char	*tmp;
	char	**collect;
	char	*value;
	int		j;

	tmp = ft_strtrim(token, "\"");
	n = exp_count(token, 0, 0);
	collect = collectexp(token, master, 0, 0);
	value = expjoin(n, collect);
	j = -1;
	while (++j < n)
	{
		if (collect[j])
			free (collect[j]);
	}
	free (collect);
	free (tmp);
	free (token);
	return (value);
}
