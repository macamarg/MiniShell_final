#include "../minishell.h"

static void	add_tokenback(t_token **token_lst, t_token *new_token)
{
	t_token	*iter;

	if (*token_lst == NULL)
	{
		*token_lst = new_token;
		return ;
	}
	else
	{
		iter = *token_lst;
		while (iter->next != NULL)
		{
			iter = iter->next;
		}
		iter->next = new_token;
		new_token->prev = iter;
	}
}

static void	new_expandtoken(char *str, t_token	**tmp_lst)
{
	t_token	*tmp_token;
	int		len;

	len = ft_strlen(str);
	tmp_token = safe_malloc(sizeof(t_token));
	tmp_token->token = safe_malloc( len + 1);
	ft_memcpy(tmp_token->token, str, len);
	tmp_token->token[len] = '\0';
	tmp_token->type = STRING;
	tmp_token->next = NULL;
	tmp_token->prev = NULL;
	*tmp_lst = NULL;
	add_tokenback(tmp_lst, tmp_token);
}

static void insert_exp(char	**splited, t_token **token_lst, t_token *prev_token, t_token *next_token)
{
	t_token	*tmp_lst;
	t_token	*iter;
	int		i;

	i = -1;
	while(splited[++i] != NULL)
		new_expandtoken(splited[i], &tmp_lst);
	iter = tmp_lst;
	while (iter->next != NULL)
		iter = iter->next;
	tmp_lst->prev = prev_token;
	iter->next =  next_token;
}

void	token_expansion(t_token **token_lst)
{
	t_token	*iter;
	char	*tmp;
	char	**splited;
	int		i;

	iter = *token_lst;
	i = -1;
	if(iter->token[0] == '"')
	{
		tmp = get_valueexp(iter->token, mini_call(), -1, 0);
		iter->token = NULL;
		splited = ft_split(tmp, ' ');
		insert_exp(splited, token_lst, iter->prev, iter->next);
		while(splited[++i] != NULL)
			free(splited[i]);
		free(splited);
	}
	else
		iter->token = get_valueexp(iter->token, mini_call(), -1, 0);
}
