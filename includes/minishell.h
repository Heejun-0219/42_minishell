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
	//TODO : ; 추가
	KEY,		
	PIPE,				// |
	REDIRECT,			// > >> < <<
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;	// KEY, PIPE, REDIRECT
	char			*s;		// token string -> ex) ls, |, >, >>
	size_t			token_index; // 해당 토큰 인덱스 -> 위치 
}	t_token;

typedef struct s_parse
{
	size_t			line_index;		// line 인덱스
	char			*line;			// line
	size_t			token_count;	// 토큰 개수
	t_token			*tokens;		// 토큰 배열
}	t_parse;

typedef enum e_redirect_type
{
	OUT_ONE,
	OUT_TWO,
	IN,
	HERE,
}	t_redirect_type;

typedef struct s_redirect
{
	t_redirect_type		type;
	char				*value;
}	t_redirect;

typedef struct s_pipe
{
	char			*cmd_path;
	char			**cmd;
	size_t			cmd_index;
	t_redirect		*redirect;
	size_t			redirect_index;
	pid_t			pid;
	int				pipe_fd[2];
	int				in_fd;
	int				out_fd;
}	t_pipe;

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

void    sig_handler(int signo);
void    init_sig(t_info *info);

void    init_info(t_info *info, int ac, char **av, char **env);
void    init_env_list(t_info *info, char **env);
int     ft_list_push_back(t_list *list, void *content);

// parsing
void tokenize_line(t_parse *parse);

// parsing/quoter_util.c
void merge_and_free_tokens(char **dest, char *src);
int ends_with_quote(char *token);
size_t get_array_size(char **array);

#endif