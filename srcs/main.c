#include "minishell.h"

int	ft_error(char *m, int error)
{
	printf("Error\n%s\n", m);
	return (error);
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