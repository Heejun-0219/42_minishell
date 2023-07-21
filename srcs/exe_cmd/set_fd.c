/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:50:05 by heejunki          #+#    #+#             */
/*   Updated: 2023/07/11 15:50:08 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_pipe_fd(t_cmd *cmd, t_pipe *pipe)
{
	if (cmd->pre_pipe_fd != -1)
	{
		if (dup2(cmd->pre_pipe_fd, STDIN_FILENO) == FAILURE)
			exit(ft_perror(errno));
		if (close(cmd->pre_pipe_fd) == FAILURE)
			exit(ft_perror(errno));
	}
	if (pipe->is_pipe == TRUE)
	{
		if (dup2(pipe->pipe_fd[OUT], STDOUT_FILENO) == FAILURE)
			exit(ft_perror(errno));
		if (close(pipe->pipe_fd[OUT]) == FAILURE)
			exit(ft_perror(errno));
		if (close(pipe->pipe_fd[IN]) == FAILURE)
			exit(ft_perror(errno));
	}
}

void	set_fd(t_cmd *cmd, t_pipe *pipe)
{
	set_pipe_fd(cmd, pipe);
	set_redirect_fd(pipe);
	if (pipe->in_fd != -1)
	{
		if (dup2(pipe->in_fd, STDIN_FILENO) == FAILURE)
			exit(ft_perror(errno));
		if (close(pipe->in_fd) == FAILURE)
			exit(ft_perror(errno));
	}
	if (pipe->out_fd != -1)
	{
		if (dup2(pipe->out_fd, STDOUT_FILENO) == FAILURE)
			exit(ft_perror(errno));
		if (close(pipe->out_fd) == FAILURE)
			exit(ft_perror(errno));
	}
}
