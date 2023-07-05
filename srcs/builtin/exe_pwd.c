#include "minishell.h"

int exe_pwd(t_parse *parse, t_cmd *cmd, t_info *info, t_pipe *pipe)
{
    char pwd[256];

    (void)parse;
    (void)cmd;
    (void)info;
    (void)pipe;
    if (getcwd(pwd, 256))
        printf("%s\n", pwd);
    else
        exit(EXIT_FAILURE);
    exit(EXIT_SUCCESS)
}
    