/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:36:45 by heejunki          #+#    #+#             */
/*   Updated: 2023/07/06 14:45:59 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	close_free(char *line, int fd, char *limiter)
{
	if (close(fd) == FAILURE)
		exit(ft_perror(errno));
	free(line);
	free(limiter);
	return (SUCCESS);
}

void	tmp_heredoc(t_redirect *redirect)
{
	char	*line;
	char	*limiter;
	int		fd;

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
		free(line);
	}
	close_free(line, fd, limiter);
}

void	heredoc_child(t_cmd *cmd)
{
	t_redirect	*redirect;
	t_pipe		*pipe;

	signal(SIGINT, sig_heredoc_child);
	cmd->pipe_index = 0;
	while (cmd->pipe_index < cmd->pipe_count)
	{
		pipe = &cmd->pipe[cmd->pipe_index];
		pipe->redirect_index = 0;
		while (pipe->redirect[pipe->redirect_index].val != 0)
		{
			redirect = &pipe->redirect[pipe->redirect_index];
			if (redirect->type == HEREDOC)
				tmp_heredoc(redirect);
			pipe->redirect_index++;
		}
		cmd->pipe_index++;
	}
	exit(EXIT_SUCCESS);
}

int	is_heredoc(t_cmd *cmd)
{
	int		i;
	pid_t	pid;

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
