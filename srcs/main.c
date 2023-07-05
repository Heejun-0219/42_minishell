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
    size_t  line_index;    // line 인덱스, 나중에 

    init_info(&info, ac, av, env);
    line_index = 0;
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
        tokenize_line(&parse);
        parse.line_index = line_index++;
        add_history(parse.line);
        free(parse.line);
    }
    return (SUCCESS);
}