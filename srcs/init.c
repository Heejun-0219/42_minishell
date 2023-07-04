#include "minishell.h"

int g_exit_code;

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