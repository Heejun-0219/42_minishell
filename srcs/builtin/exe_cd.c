#include "minishell.h"

int exe_cd(t_parse *parse, t_cmd *cmd, t_info *info, t_pipe *pipe)
{
    char    *path;

    (void)parse;
    (void)cmd;
    (void)info;
    path = pipe->cmd[1];
    if (path == NULL)
    {
        if (pipe->builtin == TRUE)
            return (SUCCESS);
        else
            exit(EXIT_SUCCESS);
    }
    if (chdir(path) == FAILURE)
    {
        g_exit_code = 1;
        if (pipe->builtin == TRUE)
        {
            printf("minishell: cd: %s: %s\n", path, strerror(errno));
            return (ft_perror(SUCCESS));
        }
        else
            exit(EXIT_SUCCESS);
    }
    if (pipe->builtin == TRUE)
        return (SUCCESS);
    else
        exit(EXIT_SUCCESS);
}