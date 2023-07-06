/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:25:04 by heejunki          #+#    #+#             */
/*   Updated: 2023/07/06 16:48:43 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <errno.h>
# include "libft.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define SUCCESS 0
# define FAILURE -1
# define ERROR 1
# define TRUE 1
# define FALSE 0
# define PROMPT "minishell$ "

extern int	g_exit_code;

typedef struct s_node
{
	void			*content;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_list
{
	t_node			*front;
	t_node			*back;
	t_node			*cur;
}	t_list;

typedef enum e_token_type
{
	KEY,
	PIPE,
	REDIRECT,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*s;
	size_t			token_index;
}	t_token;

typedef struct s_parse
{
	char			*line;
	size_t			line_index;
	size_t			token_count;
	t_token			*tokens;
}	t_parse;

typedef enum e_redirect_type
{
	WRITE,
	APPEND,
	READ,
	HEREDOC,
}	t_redirect_type;

typedef struct s_redirect
{
	t_redirect_type		type;
	char				*val;
}	t_redirect;

typedef struct s_pipe
{
	char			*cmd_path;
	char			**cmd;
	size_t			cmd_index;
	t_redirect		*redirect;
	size_t			redirect_index;
	pid_t			pid;
	int				is_pipe;
	int				pipe_fd[2];
	int				in_fd;
	int				out_fd;
	int				builtin;
}	t_pipe;

typedef struct s_cmd
{
	t_pipe			*pipe;
	size_t			pipe_count;
	size_t			pipe_index;
	int				pre_pipe_fd;
	char			**envp;
	pid_t			pid;
}	t_cmd;

typedef struct s_info
{
	int				ac;
	char			**av;
	char			**env;
	t_list			env_list;
	struct termios	term;
	struct termios	term_back;
}	t_info;

void	ft_lstclear(t_list *lst);
int		ft_lstdel_node(t_list *list, t_node *node);
int		ft_lstpush_back(t_list *list, void *content);
t_list	ft_lst_init(void);

int		ft_perror(int error);
int		ft_error(char *m, int error);
void	free_mini(t_parse *parse, t_cmd *cmd);
void	free_tokens(t_parse *parse, size_t token_size);
void	free_cmd(t_cmd *cmd, size_t pipe_i);
int		ft_error(char *m, int error);

void	sig_handler(int signo);
void	init_sig(t_info *info);
void	sig_heredoc_parent(int signo);
void	sig_heredoc_child(int signo);

void	init_info(t_info *info, int ac, char **av, char **env);
void	init_env_list(t_info *info, char **env);

char	*get_env_val(char *key, t_info *info);
int		if_env_change(t_info *info, t_parse *parse);

int		make_cmd_info(t_parse *parse, t_cmd *cmd, t_info *info);
void	init_pipe(t_pipe *pipe);
int		init_cmd(t_parse *parse, t_cmd *cmd, t_info *info);
int		get_path_env(t_parse *parse, t_cmd *cmd, t_info *info);
void	get_exe_count(t_parse *parse, t_cmd *cmd);

char	*get_env_val(char *key, t_info *info);

int		make_pipe(t_parse *parse, t_cmd *cmd);
int		set_pipe(t_parse *parse, t_pipe *pipe, size_t index);
int		set_re(t_parse *parse, t_pipe *pipe, size_t index);
void	set_key(t_parse *parse, t_pipe *pipe, size_t index);
int		malloc_re(t_parse *parse, t_pipe *pipe);
int		malloc_cmd(t_parse *parse, t_pipe *pipe);

int		exe_cmd(t_parse *parse, t_cmd *cmd, t_info *info);
int		wait_mini(t_cmd *cmd);

int		is_heredoc(t_cmd *cmd);
void	heredoc_child(t_cmd *cmd);
void	tmp_heredoc(t_redirect *redirect);

int		check_builtin(t_pipe *pipe);
int		check_builtin_parent(t_cmd *cmd, t_pipe *pipe);
int		exe_builtin(t_parse *parse, t_cmd *cmd, t_info *info, t_pipe *pipe);
int		exe_builtin_parent(t_parse *parse, t_cmd *cmd, t_info *info, \
		t_pipe *pipe);

int		exe_cd(t_pipe *pipe);
int		exe_echo(t_pipe *pipe);
int		exe_env(t_parse *parse, t_cmd *cmd, t_info *info, t_pipe *pipe);
int		exe_exit(t_parse *parse, t_cmd *cmd, t_info *info, t_pipe *pipe);
int		exe_export(t_parse *parse, t_cmd *cmd, t_info *info, t_pipe *pipe);
t_node	*get_if_env_exist(t_list *env_list, const char *s);
int		check_valid(char *str);
int		exe_pwd(void);
int		exe_unset(t_info *info, t_pipe *pipe);

// parsing
void	tokenize_line(t_parse *parse);

// // quoter
// void merge_quoted_tokens(char **tokens_str);
// void merge_tokens(char **tokens_str, int *i, int *j, int *quoter_type);
// void check_toggle_quote_type(char **tokens_str, int i, int *quoter_type);

// parsing/quoter_util.c
void	merge_and_free_tokens(char **dest, char *src);
int		ends_with_quote(char *token);
size_t	get_array_size(char **array);
int		is_end_of_quote_scope(char *token, int inside_double, \
	int inside_single);

#endif