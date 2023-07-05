#include "minishell.h"

void    tmp_heredoc(t_redirect *redirect)
{
    char    *line;
    char    *limiter;
    int     fd;

    fd = open("/tmp/whine", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0644);
    if (fd == FAILURE)
        exit(ft_perror(errno));
    limiter = ft_strjoin(redirect->val, "\n");
    if (limiter == NULL)
        exit(ft_error("malloc error\n", FAILURE));
    while (TRUE)
    {
        write (STDOUT_FILENO, "> ", 2);
        line = readline("");
        if (line == NULL)
            exit(ft_perror(errno));
        if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == TRUE)
        {
            free(line);
            break ;
        }
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
    free(line);
    free(limiter);
    if (close(fd) == FAILURE)
        exit(ft_perror(errno));
}

void    heredoc_child(t_cmd *cmd)
{
    size_t      i;
    t_redirect  *redirect;
    t_pipe      *pipe;

    signal(SIGINT, sig_heredoc_child);
    i = 0;
    while (i < cmd->pipe_count)
    {
        pipe = &cmd->pipe[i];
        pipe->redirect_index = 0;
        while (pipe->redirect[pipe->redirect_index].type != 0)
        {
            redirect = &pipe->redirect[pipe->redirect_index];
            if (redirect->type == HEREDOC)
                tmp_heredoc(redirect);
            pipe->redirect_index++;
        }
        i++;
    }
    exit(EXIT_SUCCESS);
}

int is_heredoc(t_cmd *cmd)
{
    int     i;
    pid_t   pid;

    pid = fork();
    if (pid == FAILURE)
        return (ft_error("fork error\n", FAILURE));
    else if (pid == 0)
        heredoc_child(cmd);
    signal(SIGINT, sig_heredoc_parent);
    if (waitpid(-1, &i, 0) == FAILURE)
        return (ft_perror(FAILURE));
    g_exit_code = WEXITSTATUS(i);
    if (g_exit_code == EXIT_FAILURE)
        return (FAILURE);
    return (SUCCESS);
}
