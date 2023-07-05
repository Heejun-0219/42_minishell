#include "minishell.h"

void get_exe_count(t_parse *parse, t_cmd *cmd)
{
    size_t i;

    i = 0;
    cmd->pipe_count = 1;
    while (i < parse->token_count)
    {
        if (parse->tokens[i].type == KEY)
            cmd->pipe_count++;
        i++;
    }
}

int get_path_env(t_parse *parse, t_cmd *cmd, t_info *info)
{
    char    *path;
    t_node  *node;

    node = info->env_list.front;
    while (node && ft_strncmp(node->content, "PATH=", 5))
        node = node->next;
    if (node == NULL)
    {
        cmd->envp = (char **)malloc(sizeof(char *) * 2);
        if (cmd->envp == NULL)
            return (ft_error("malloc error\n", FAILURE));
        return (SUCCESS);
    }
    path = ft_strdup(node->content + 5);
    if (path == NULL)
        return (ft_error("malloc error\n", FAILURE));
    cmd->envp = ft_split(path, ':');
    if (cmd->envp == NULL)
    {
        free_tokens(parse, parse->token_count);
        return (ft_error("malloc error\n", FAILURE));
    }
    return (SUCCESS);
}

int init_cmd(t_parse *parse, t_cmd *cmd, t_info *info)
{
    if (get_path_env(parse, cmd, info) == FAILURE)
        return (FAILURE);
    cmd->pipe_index = 0;
    cmd->pre_pipe_fd = -1;
    cmd->pipe = (t_pipe *)malloc(sizeof(t_pipe) * cmd->pipe_count);
    if (cmd->pipe == NULL)
    {
        free(cmd->envp);
        free_tokens(parse, parse->token_count);
        return (ft_error("malloc error\n", FAILURE));
    }
    return (SUCCESS);
}

void    init_pipe(t_pipe *pipe)
{
    pipe->cmd_path = NULL;
    pipe->cmd = NULL;
    pipe->cmd_index = 0;
    pipe->redirect = NULL;
    pipe->redirect_index = 0;
    pipe->pid = FALSE;
    pipe->is_pipe = FALSE;
    pipe->pipe_fd[0] = FAILURE;
    pipe->pipe_fd[1] = FAILURE;
    pipe->in_fd = FAILURE;
    pipe->out_fd = FAILURE;
    pipe->builtin = FALSE;
}

int make_cmd_info(t_parse *parse, t_cmd *cmd, t_info *info)
{
    get_exe_count(parse, cmd);
    if (init_cmd(parse, cmd, info) == FAILURE)
        return (FAILURE);
    if (make_pipe(parse, cmd) == FAILURE)
    {
        free_tokens(parse, parse->token_count);
        return (FAILURE);
    }
    return (SUCCESS);
}