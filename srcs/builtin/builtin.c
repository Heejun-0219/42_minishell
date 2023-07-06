#include "minishell.h"

int is_builtin(t_cmd *cmd, t_pipe *pipe)
{
    if (cmd->pipe[cmd->pipe_index].cmd == NULL)
        return (FALSE);
    if (cmd->pipe_index != FALSE || pipe->is_pipe == TRUE)
        return (FALSE);
    if (pipe->cmd_path == NULL)
        return (FALSE);
    if (ft_strncmp(pipe->cmd[0], "echo", 5) == TRUE)
        return (TRUE);
    if (ft_strncmp(pipe->cmd[0], "cd", 3) == TRUE)
        return (TRUE);
    if (ft_strncmp(pipe->cmd[0], "pwd", 4) == TRUE)
        return (TRUE);
    if (ft_strncmp(pipe->cmd[0], "export", 7) == TRUE)
        return (TRUE);
    if (ft_strncmp(pipe->cmd[0], "unset", 6) == TRUE)
        return (TRUE);
    if (ft_strncmp(pipe->cmd[0], "env", 4) == TRUE)
        return (TRUE);
    if (ft_strncmp(pipe->cmd[0], "exit", 5) == TRUE)
        return (TRUE);
    return (FALSE);
}

int exe_builtin(t_parse *parse, t_cmd *cmd, t_info *info, t_pipe *pipe)
{
    pipe->builtin = TRUE;
    if (ft_strncmp(pipe->cmd[0], "echo", 5) == TRUE)
        return (exe_echo(parse, cmd, info, pipe));
    if (ft_strncmp(pipe->cmd[0], "cd", 3) == TRUE)
        return (exe_cd(parse, cmd, info, pipe));
    if (ft_strncmp(pipe->cmd[0], "pwd", 4) == TRUE)
        return (exe_pwd(parse, cmd, info, pipe));
    
    
    if (ft_strncmp(pipe->cmd[0], "unset", 6) == TRUE)
        return (exe_unset(parse, cmd, info, pipe));
    if (ft_strncmp(pipe->cmd[0], "env", 4) == TRUE)
        return (exe_env(parse, cmd, info, pipe));
    if (ft_strncmp(pipe->cmd[0], "exit", 5) == TRUE)
        return (exe_exit(parse, cmd, info, pipe));
    return (SUCCESS);
}
