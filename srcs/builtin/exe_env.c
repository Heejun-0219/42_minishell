#include "minishell.h"

int diff_env_export(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '=')
            return (TRUE);
        i++;
    }
    return (FALSE);
}

int exe_env(t_parse *parse, t_cmd *cmd, t_info *info, t_pipe *pipe)
{
    t_node  *node;

    (void)parse;
    (void)cmd;
    (void)pipe;
    node = info->env.front;
    while (node)
    {
        if (diff_env_export(node->content) == TRUE)
            printf("%s\n", node->content);
        node = node->next;
    }
    exit(EXIT_SUCCESS);
}
