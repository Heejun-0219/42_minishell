#include "minishell.h"

int	ft_error(char *m, int error)
{
	printf("Error\n%s\n", m);
	return (error);
}

void    sig_handler(int signo)
{
    (void)signo;
	g_exit_code = 1;
	printf("\n");
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1);
	rl_redisplay();
}

void    init_sig(t_info *info)
{
    info->term = info->term_back;
    info->term.c_lflag = ~ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, &info->term);
    signal(SIGINT, sig_handler);
    signal(SIGQUIT, SIG_IGN);
}

int main(int ac, char **av, char **env)
{
    char *line;
    t_info info;

    init_info(&info, ac, av, env);
    while (TRUE)
    {
        init_sig(&info);
        line = readline(PROMPT);
        if (line == NULL)
        {
            ft_lstclear(&info.env_list);
            printf("\x1b[1A\033[11Cexit\n");
            break ;
        }
        if (line[0] == '\0')
        {
            free(line);
            continue ;
        }
        add_history(line);
        free(line);
    }
    return (SUCCESS);
}