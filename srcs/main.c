#include "minishell.h"

static int parse_exe(t_parse *parse, t_cmd *cmd, t_info *info)
{
    // parse | info 환경변수 확인? 

    if (make_cmd_info(parse, cmd, info) == FAILURE)
        return (FAILURE);
    if (exe_cmd(parse, cmd, info) == FAILURE)
        return (FAILURE);
    free_mini(parse, cmd);
}

int main(int ac, char **av, char **env)
{
    t_parse parse;
    t_info  info;
    t_cmd   cmd;
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
        parse.line_index = line_index++; 
        add_history(parse.line);
        parse_exe(&parse, &cmd, &info);
        free(parse.line);
    }
    return (SUCCESS);
}