#include "minishell.h"

static void export_option(t_info *info, t_pipe *pipe)
{
    size_t  i;
    t_node  *node;

    i = 1;
    while (pipe->cmd[i])
    {
        
        i++;
    }
}

static void export_no(t_list *env_list)
{
    t_list *env;

    env = env_list->front;
    while (env)
    {
        printf("declare -x %s\n", (char *)(env->content));
        env = env->next;
    }
}

int exe_export(t_parse *parse, t_cmd *cmd, t_info *info, t_pipe *pipe)
{
    (void)parse;
    (void)cmd;
    if (pipe->cmd[1] == NULL)
        export_no(&(info->env_list));
    else
        export_option(info, pipe);
    if (pipe->builtin == TRUE)
        return (SUCCESS);
    else
        exit(SUCCESS);
}
