/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macamarg <macamarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:21:56 by macamarg          #+#    #+#             */
/*   Updated: 2025/02/19 10:38:52 by macamarg         ###   ########.fr       */
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
		if (token[i] == '$' && token[i + 1] != '\0')
		{
			if (j != i)
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
	if (j != i)
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
	n = exp_count(tmp, 0, 0);
	collect = collectexp(tmp, master, 0, 0);
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
