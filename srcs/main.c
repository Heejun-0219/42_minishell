#include "minishell.h"

int	ft_error(char *m, int error)
{
	printf("Error\n%s\n", m);
	return (error);
}

int main(int ac, char **av, char **env)
{
    t_parse parse;
    t_info  info;

    init_info(&info, ac, av, env);
    while (TRUE)
    {
        init_sig(&info);
        parse.line = readline(PROMPT);
        if (parse.line == NULL)
        {
            ft_lstclear(&info.env_list);
            printf("\x1b[1A\033[11Cexit\n");
            break ;
        }
        if (parse.line[0] == '\0')
        {
            free(parse.line);
            continue ;
        }
        add_history(parse.line);
        free(parse.line);
    }
    return (SUCCESS);
}