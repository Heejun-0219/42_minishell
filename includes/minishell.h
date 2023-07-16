/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:25:04 by heejunki          #+#    #+#             */
/*   Updated: 2023/07/16 20:13:33 by mi               ###   ########.fr       */
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
# define IN 0
# define OUT 1
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

typedef struct s_cha_env
{
	t_token			*token;
	size_t			token_index;
	size_t			string_index;
	char			*exit_code;
	char			*tmp1;
	char			*tmp2;
	size_t			start;
	size_t env_len;
	char *env;
	char *target;
	size_t target_len;
} t_cha_env;

typedef struct s_parse
{
	char *line;
	size_t line_index;
	size_t token_count;
	t_token *tokens;
} t_parse;

typedef struct s_del_quote
{
	char *str;
	int index;
	int subordinate;
	struct s_del_quote *next;
} t_del_quote;

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
	int				last_c;
	char			**last_v;
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
void	sig_parent(int signo);

void	init_info(t_info *info, int ac, char **av, char **env);
void	init_env_list(t_info *info, char **env);

char	*get_env_val(char *key, t_info *info);
int		if_env_change(t_info *info, t_parse *parse);

int		change_special_env(t_info *info, t_cha_env *cv);
int		change_abs(t_info *info, t_cha_env *cv);

int		syntax_error(t_parse *parse);
void	backslash_to_space(t_parse *parse, size_t i);
int		make_cmd_info(t_parse *parse, t_cmd *cmd, t_info *info);
void	init_pipe(t_pipe *pipe);
int		init_cmd(t_parse *parse, t_cmd *cmd, t_info *info);
int		get_path_env(t_parse *parse, t_cmd *cmd, t_info *info);
void	get_exe_count(t_parse *parse, t_cmd *cmd);

char	*get_env_val(char *key, t_info *info);

int		make_pipe(t_parse *parse, t_cmd *cmd);
int		set_pipe(t_parse *parse, t_pipe *pipe, size_t *index);
int		check_here(char s1, char s2);
void	set_re(t_parse *parse, t_pipe *pipe, size_t index);
void	set_key(t_parse *parse, t_pipe *pipe, size_t index);
int		malloc_re(t_parse *parse, t_pipe *pipe, size_t index);
int		malloc_cmd(t_parse *parse, t_pipe *pipe, size_t index);

void	exe_child(t_info *info, t_parse *parse, t_cmd *cmd, t_pipe *pipe);

void	set_fd(t_cmd *cmd, t_pipe *pipe);
void	set_redirect_fd(t_pipe *pipe);

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

int		exe_cd(t_pipe *pipe, t_info *info);
int		exe_echo(t_pipe *pipe);
int		exe_env(t_parse *parse, t_cmd *cmd, t_info *info, t_pipe *pipe);
int		exe_exit(t_parse *parse, t_cmd *cmd, t_info *info, t_pipe *pipe);
int		exe_export(t_parse *parse, t_cmd *cmd, t_info *info, t_pipe *pipe);
void	export_c(t_list *env_list, char c);
t_node	*get_if_env_exist(t_list *env_list, const char *s);
int		check_valid(char *str);
int		exe_pwd(void);
int		exe_unset(t_info *info, t_pipe *pipe);

// parsing.c
void tokenize_line(t_parse *parse);
t_token set_token(char *token_str, int index);

// parsing_utils.c
int count_strs(char **strs);

// quote.c
char **split_respect_quote(char *str, char c);
char	**alloc_split_dismiss_quote(char **result, char *str, char c, int count);
int len_respect_quote(char *str, char c);
int get_count_respect_quote(char *str, char c);
char *check_quote_set_flag(char *str, int *flag);

// quote_utils.c
char *push_str_to_endpoint(char *str, char endpoint);

// node_free.c
void destroy_nodes(t_del_quote **head);
void free_node(t_del_quote *node);

// remove_quote_node.c
void copy_data_to_node(t_del_quote **head, char **strs);
t_del_quote *new_del_quote_node(char *str, int index, int subordinate);
t_del_quote *copy_node(t_del_quote *node);

// remove_quote.c
char **remove_quote(char **strs);
void modify_index(t_del_quote **head);
void dequote(t_del_quote **head);
void split_quote(t_del_quote **head);
char **dequoted_merge(t_del_quote **head);

// split_quote_utils.c
t_del_quote *new_quote_split_list(t_del_quote **head, t_del_quote *current);
char **make_quote_split_strs(char *str);
int quote_split_strs_count(char *str);
void rearrange_index(t_del_quote **head);
int check_one_word(char *str);
int check_one_word_push_to_endpoint(char *str, char c);
int len_one_word(char *str);
int get_strs_count(t_del_quote *head);

#endif