#include "minishell.h"

static void exit_option(t_pipe *pipe)
{
    int i;
    int print_operator;

    print_operator = FALSE;
    i = 0;
    if (pipe->cmd[pipe->cmd_index].cmd[1][0] == '-' \
        || pipe->cmd[pipe->cmd_index].cmd[1][0] == '+')
    {
        print_operator = TRUE;
        i++;
    }
    while (pipe->cmd[1][i])
    {
        if (ft_isdigit(pipe->cmd[1][i]) == FALSE)
        {
            printf("exit\n");
            printf("minishell: exit: %s: numeric argument required\n", \
                pipe->cmd[1]);
            exit(255);
        }
        i++;
    }
    if (i == 1 && print_operator == TRUE)
    {
        printf("exit\n");
        printf("minishell: exit: %s: numeric argument required\n", \
            pipe->cmd[1]);
        exit(255);
    }
}

static void exit_no_option(t_parse *parse, t_cmd *cmd, \
    t_info *info, t_pipe *pipe)
{
    if (cmd->pipe[cmd->pipe_index].cmd[1] == NULL)
    {
        ft_lstclear(info->env_list);
        free_mini(parse, cmd);
        if (pipe->builtin == TRUE)
            printf("exit\n");
        exit(EXIT_SUCCESS);
    }
}

int exe_exit(t_parse *parse, t_cmd *cmd, t_info *info, t_pipe *pipe)
{
    int exit_val;

    exit_no_option(parse, cmd, info, pipe);
    exit_option(pipe)
    exit_val = ft_atoi(cmd->pipe[cmd->pipe_index].cmd[1]);
    ft_lstclear(info->env_list);
    free_mini(parse, cmd);
    exit(exit_val);
}
