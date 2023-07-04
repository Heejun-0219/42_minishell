#include "minishell.h"

int g_exit_code;

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

void    init_env_list(t_info *info, char **env)
{
    size_t  i;

    i = 0;
    info->env_list = ft_lst_init();
    while (env[i] != NULL)
    {
        ft_lstpush_back(&info->env_list, ft_strdup(env[i]));
        i++;
    }
}

void    init_info(t_info *info, int ac, char **av, char **env)
{
    g_exit_code = 0;
    info->ac = ac;
    info->av = av;
    info->env = env;
    tcgetattr(STDIN_FILENO, &info->term_back);
    init_env_list(info, env);
}