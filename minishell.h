/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:07:09 by macamarg          #+#    #+#             */
/*   Updated: 2025/02/19 11:06:18 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
//readline

# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
//boolean
# include <stdbool.h>

# include "libft/libft.h"

typedef enum e_err
{
	SYNTAX,
}	t_err;

/*
	STRING(0), llllll; "a<>|", 'a<>|$'
	REDIR_IN(1), <
	REDIR_OUTA(2), >>
	REDIR_OUTW(3), >
	PATH_IN (4), after <
	PATH_OUTA(5), after >>
	PATH_OUTW(6), after >
	PIPE(7), |
	EXPAND(8), "$"; $
	HEREDOC(9), <<
	ENDFILE(10), after <<
*/

# define READ_END 0
# define WRITE_END 1

# define INFILE 1
# define OUTFILE 2

# define FIRST 0
# define MIDLE 1
# define LAST 2

typedef enum e_class
{
	STRING,
	REDIR_IN,
	REDIR_OUTA,
	REDIR_OUTW,
	PATH_IN,
	PATH_OUT,
	PIPE,
	EXPAND,
	HEREDOC,
	ENDFILE,
}	t_class;


typedef enum e_type
{
	EXEC,
	ECHO,
	CD,
	PWD,
}	t_type;

typedef struct s_split
{
	char	*start;
	int		end;
}	t_split;


typedef struct s_token
{
	struct s_token	*prev;
	struct s_token	*next;
	char			*token;
	int				type;
}	t_token;

typedef struct s_count
{
	int	cmd_n;
	int	redirin_n;
	int	redirout_n;
	int	heredoc_n;
	int	expand_n;
	int	pipe;
}	t_count;

typedef struct s_command
{
	struct s_command	*prev;
	struct s_command	*next;
	int					type;//
	char				**cmd;
	char				*cmd_path;
	char				**redir_in;//path in
	char				**redir_out;//path out
	char				**end_file;
	char				**expand;
	bool				pipe;
	int					fd_in;//read in
	int					fd_out;//write out
	int					order;
	int					heredoc_n;
}	t_command;

typedef struct s_env
{
	struct s_env	*next;
	char			*env_var;
}	t_env;

typedef struct s_minishell
{
	char		*prompt;
	char		**env;
	t_env		*envp;
	t_env		*export;
	char		**argv;
	char		*local_dir;
	bool		prompt_status;
	int			last_status;
	int			str_n;
	t_token		**token_lst;
	t_command	**cmd_lst;
}	t_minishell;

//readline
void	ft_getprompt(t_minishell *master);

//parse
void	ft_parseline(t_minishell *master);

//tokenlst
void	make_tokenlst(t_minishell *master);
void	print_tokenlst(t_token **token_lst);
void	class_token(t_minishell *master);

//cmd struct
void	cmd_structfill(t_minishell *master);
void	print_cmdlst(t_command *cmd_lst);
char	*quotes_rm(t_token *iter);
void	redir_handler(t_minishell *master);
int		redir_heredoc(char *eof);
char	**cmd_fill(t_token **token_lst, int count, int t_class);

//expand
char			*std_exp(char *tmp, t_minishell *master, int i);
char			*get_valueexp(char *token, t_minishell *master, int i, int n);
char			*collectprior(char *token, int i, int j);

//redir
void	ft_find_redir(t_minishell *master);

//clean
void	ft_clean_ms(t_minishell *master);
void	ft_clean_env(t_env *envp, char **env);
void	ft_clean_cmd(t_command **cmd_lst);
void	ft_clean_token(t_token **token_lst);

//minicall
t_minishell	*mini_call(void);

///env
char **env_cpy_arr(t_env *envp, int count);
unsigned int	env_count(t_env *envp);
void	print_env(char **env);
void	print_envp(t_env *env);


//exec
void	mini_exec(t_minishell *master);
char	*get_cmdpath(t_minishell *master, t_command *cmd);
int		is_builtin(char *command);
void	exec_cmd(t_minishell *master, t_command *cmd);
void	exec_pipeline(t_minishell *master, t_command *cmd);
void	add_shell_level(t_minishell *master);

//builtin
int		exec_builtin(t_command *cmd, t_minishell *master);
int		exec_other(t_command *cmd, t_minishell *master);
int		ft_echo(t_command *cmd);
int		ft_pwd(t_command *cmd);
int 	ft_cd(t_command *cmd, t_minishell *master);
int		ft_env(t_command *cmd, t_minishell *master);
int		ft_unset(t_command *cmd, t_minishell *master);
int		ft_export(t_command *cmd, t_minishell *master);
void	ft_change_variable_value(t_minishell *master, char *var, int flag);
int		ft_exit(t_command *cmd, t_minishell *master);
void	print_sorted_env(t_minishell *master);
void	*sort_env(t_minishell *master, char **env);

//clean
void	ft_clean_ms(t_minishell *master);
void	ft_clean_env(t_env *envp, char **env);
void	ft_clean_cmd(t_command **cmd_lst);
void	ft_clean_token(t_token **token_lst);
void	close_cmd_list_fds(t_command *cmd_lst);
void	free_array(char **array);

//error
void	error_cmdnfound(t_minishell*master, char **cmd);

//tests
void	print_cmd_paths(t_command *cmd_lst);
void	print_paths(char **paths);
void	print_order(t_command *cmd_lst);
void	print_fd(t_minishell *master);

#endif