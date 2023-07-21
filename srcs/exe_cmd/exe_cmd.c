/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:41:22 by heejunki          #+#    #+#             */
/*   Updated: 2023/07/11 15:48:13 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_mini(t_cmd *cmd)
{
	int		status;
	pid_t	pid;

	pid = cmd->pipe[cmd->pipe_count - 1].pid;
	cmd->pipe_index = 0;
	while (cmd->pipe_index < cmd->pipe_count)
	{
		cmd->pid = waitpid(-1, &status, 0);
		if (cmd->pid == FAILURE)
			return (ft_perror(errno));
		if (pid == cmd->pid)
		{
			if (WIFSIGNALED(status) == TRUE)
				g_exit_code = 128 + WTERMSIG(status);
			else
				g_exit_code = WEXITSTATUS(status);
		}
		g_exit_code = WEXITSTATUS(status);
		cmd->pipe_index++;
	}
	unlink("/tmp/mini");
	return (SUCCESS);
}

static int	close_pipe(t_cmd *cmd, t_pipe *pipe)
{
	signal(SIGINT, sig_parent);
	signal(SIGQUIT, sig_parent);
	if (cmd->pre_pipe_fd != -1)
	{
		if (close(cmd->pre_pipe_fd) == FAILURE)
			return (ft_perror(FAILURE));
	}
	if (pipe->is_pipe == TRUE)
	{
		if (close(pipe->pipe_fd[OUT]) == FAILURE)
			return (ft_perror(FAILURE));
		cmd->pre_pipe_fd = pipe->pipe_fd[IN];
	}
	else
		cmd->pre_pipe_fd = -1;
	return (SUCCESS);
}

static int	exe_pipe(t_info *info, t_parse *parse, t_cmd *cmd, t_pipe *pipe)
{
	pipe->pid = fork();
	if (pipe->pid == FAILURE)
		return (ft_perror(errno));
	else if (pipe->pid == 0)
		exe_child(info, parse, cmd, pipe);
	else
	{
		if (close_pipe(cmd, pipe) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	exe_cmd(t_parse *parse, t_cmd *cmd, t_info *info)
{
	t_pipe	*tmp_pipe;

	if (is_heredoc(cmd) == FAILURE)
		return (FAILURE);
	cmd->pipe_index = 0;
	while (cmd->pipe_index < cmd->pipe_count)
	{
		tmp_pipe = &cmd->pipe[cmd->pipe_index];
		if (check_builtin_parent(cmd, tmp_pipe) == TRUE)
			return (exe_builtin_parent(parse, cmd, info, tmp_pipe));
		if (tmp_pipe->is_pipe == TRUE)
		{
			if (pipe(tmp_pipe->pipe_fd) == FAILURE)
				return (ft_perror(FAILURE));
		}
		if (exe_pipe(info, parse, cmd, tmp_pipe) == FAILURE)
			return (FAILURE);
		cmd->pipe_index++;
	}
	wait_mini(cmd);
	return (SUCCESS);
}
