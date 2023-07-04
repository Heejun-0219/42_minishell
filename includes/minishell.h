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
	struct s_node	*next_node;
	struct s_node	*prev_node;
}	t_node;

typedef struct s_list
{
	t_node			*front_node;
	t_node			*back_node;
	t_node			*cur_node;
}	t_list;

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
#endif