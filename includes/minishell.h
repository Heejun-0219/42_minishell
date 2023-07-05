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
}	t_token;

typedef struct s_parse
{
	size_t			line_index;
	char			*line;
	size_t			tokens_index;
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
    int             ac;
    char            **av;
    char            **env;
    t_list          env_list;
    struct termios  term;
    struct termios  term_back;
}   t_info;

void	ft_lstclear(t_list *lst);
int	    ft_lstdel_node(t_list *list, t_node *node);
int     ft_lstpush_back(t_list *list, void *content);
t_list  ft_lst_init(void);

int	    ft_error(char *m, int error);
void    free_mini(t_parse *parse, t_cmd *cmd);
void	free_tokens(t_parse *parse, size_t token_size);
void	free_cmd(t_cmd *cmd, size_t pipe_i);
int		ft_error(char *m, int error);

int		make_cmd_info(t_parse *parse, t_cmd *cmd, t_info *info);
void    init_pipe(t_pipe *pipe);
int		init_cmd(t_parse *parse, t_cmd *cmd, t_info *info);
int		get_path_env(t_parse *parse, t_cmd *cmd, t_info *info);
void	get_exe_count(t_parse *parse, t_cmd *cmd);

int		make_pipe(t_parse *parse, t_cmd *cmd);
int		set_pipe(t_parse *parse, t_pipe *pipe);
int		set_re(t_parse *parse, t_pipe *pipe, size_t index);
int		malloc_re(t_parse *parse, t_pipe *pipe);
int		malloc_cmd(t_parse *parse, t_pipe *pipe);

int 	exe_cmd(t_parse *parse, t_cmd *cmd, t_info *info);

void    sig_handler(int signo);
void    init_sig(t_info *info);

void    init_info(t_info *info, int ac, char **av, char **env);
void    init_env_list(t_info *info, char **env);

#endif