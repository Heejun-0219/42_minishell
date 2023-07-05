#include "minishell.h"

int malloc_cmd(t_parse *parse, t_pipe *pipe)
{
    size_t  i;
    size_t  token_count;

    i = 0;
    token_count = 0;
    while (i < parse->token_count)
    {
        if (parse->tokens[i].type == PIPE)
            break ;
        if (parse->tokens[i].type == REDIRECT)
            i++;
        if (parse->tokens[i].type == KEY)
            token_count++;
        i++;
    }
    pipe->cmd = (char **)malloc(sizeof(char *) * (token_count + 1));
    if (pipe->cmd == NULL)
        return (ft_error("malloc error\n", FAILURE));
    return (SUCCESS);
}

int malloc_re(t_parse *parse, t_pipe *pipe)
{
    size_t  i;
    size_t  re_count;

    i = 0;
    re_count = 0;
    while (i < parse->token_count)
    {
        if (parse->tokens[i].type == PIPE)
            break ;
        if (parse->tokens[i].type == REDIRECT)
            re_count++;
        i++;
    }
    pipe->redirect = (t_redirect *)malloc(sizeof(t_redirect) * (re_count + 1));
    if (pipe->redirect == NULL)
        return (ft_error("malloc error\n", FAILURE));
    return (SUCCESS);
}

int set_re(t_parse *parse, t_pipe *pipe, size_t index)
{
    size_t  i;

    i = index;
    if (ft_strncmp(parse->tokens[i].s, ">", 2) == TRUE)
        pipe->redirect[pipe->redirect_index].type = WRITE;
    else if (ft_strncmp(parse->tokens[i].s, ">>", 3) == TRUE)
        pipe->redirect[pipe->redirect_index].type = APPEND;
    else if (ft_strncmp(parse->tokens[i].s, "<", 2) == TRUE)
        pipe->redirect[pipe->redirect_index].type = READ;
    else if (ft_strncmp(parse->tokens[i].s, "<<", 3) == TRUE)
        pipe->redirect[pipe->redirect_index].type = HEREDOC;
    else
        return (ft_error("syntax error near unexpected token\n", FAILURE));
    pipe->redirect[pipe->redirect_index].val = \
        parse->tokens[i + 1].s;
    pipe->redirect_index++;
    return (SUCCESS);
}

int set_pipe(t_parse *parse, t_pipe *pipe)
{
    size_t  i;

    i = 0;
    if (malloc_cmd(parse, pipe) == FAILURE)
        return (FAILURE);
    if (malloc_re(parse, pipe) == FAILURE)
        return (FAILURE);
    while (i < parse->token_count)
    {
        if (parse->tokens[i].type == PIPE)
        {
            pipe->is_pipe = TRUE;
            i++;
            break ;
        }
        if (parse->tokens[i].type == KEY)
        {
            pipe->cmd[pipe->cmd_index] = parse->tokens[i].s;
            if (pipe->cmd_index == FALSE)
                pipe->cmd_path = pipe->cmd[pipe->cmd_index];
            pipe->cmd_index++;
        }
        if (parse->tokens[i].type == REDIRECT)
        {
            if (set_re(parse, pipe, i) == FAILURE)
                return (FAILURE);
            i++;
        }
        i++;
    }
    return (SUCCESS);
}

int make_pipe(t_parse *parse, t_cmd *cmd)
{
    t_pipe  *pipe;
    size_t  i;

    i = 0;
    while (i < cmd->pipe_count)
    {
        pipe = &cmd->pipe[i];
        init_pipe(pipe);
        if (set_pipe(parse, pipe) == FAILURE)
        {
            free_cmd(cmd, i);
            return (FAILURE);
        }
        i++;
    }
    return (SUCCESS);
}