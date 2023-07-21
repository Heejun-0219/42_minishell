/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_set_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:48:24 by heejunki          #+#    #+#             */
/*   Updated: 2023/07/11 15:48:47 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	re_write(t_pipe *pipe, t_redirect *redirect)
{
	if (pipe->out_fd != -1)
		if (close(pipe->out_fd) == FAILURE)
			exit(ft_perror(errno));
	pipe->out_fd = open(redirect->val, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipe->out_fd == FAILURE)
		exit(ft_perror(1));
}

static void	re_append(t_pipe *pipe, t_redirect *redirect)
{
	if (pipe->out_fd != -1)
		if (close(pipe->out_fd) == FAILURE)
			exit(ft_perror(errno));
	pipe->out_fd = open(redirect->val, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (pipe->out_fd == FAILURE)
		exit(ft_perror(1));
}

static void	re_read(t_pipe *pipe, t_redirect *redirect)
{
	if (pipe->in_fd != -1)
		if (close(pipe->in_fd) == FAILURE)
			exit(ft_perror(errno));
	pipe->in_fd = open(redirect->val, O_RDONLY);
	if (pipe->in_fd == FAILURE)
	{
		printf("minishell: %s: %s\n", redirect->val, strerror(errno));
		exit(1);
	}
}

static void	re_heredoc(t_pipe *pipe)
{
	if (pipe->in_fd != -1)
		if (close(pipe->in_fd) == FAILURE)
			exit(ft_perror(errno));
	pipe->in_fd = open("/tmp/mini", O_RDONLY);
	if (pipe->in_fd == FAILURE)
		exit(ft_perror(1));
}

void	set_redirect_fd(t_pipe *pipe)
{
	t_redirect	*redirect;

	pipe->redirect_index = 0;
	while (pipe->redirect[pipe->redirect_index].val != 0)
	{
		redirect = &pipe->redirect[pipe->redirect_index];
		if (redirect->type == WRITE)
			re_write(pipe, redirect);
		if (redirect->type == APPEND)
			re_append(pipe, redirect);
		if (redirect->type == READ)
			re_read(pipe, redirect);
		if (redirect->type == HEREDOC)
			re_heredoc(pipe);
		pipe->redirect_index++;
	}
}
