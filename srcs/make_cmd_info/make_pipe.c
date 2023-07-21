/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:32:41 by heejunki          #+#    #+#             */
/*   Updated: 2023/07/11 15:51:53 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_here(char s1, char s2)
{
	return (s1 == '<' && s2 == '<');
}

void	set_re(t_parse *parse, t_pipe *pipe, size_t index)
{
	size_t	i;

	i = index;
	if (ft_strncmp(parse->tokens[i].s, ">", 2) == SUCCESS)
		pipe->redirect[pipe->redirect_index].type = WRITE;
	else if (ft_strncmp(parse->tokens[i].s, ">>", 3) == SUCCESS)
		pipe->redirect[pipe->redirect_index].type = APPEND;
	else if (ft_strncmp(parse->tokens[i].s, "<", 2) == SUCCESS)
		pipe->redirect[pipe->redirect_index].type = READ;
	else if (ft_strncmp(parse->tokens[i].s, "<<", 3) == SUCCESS)
		pipe->redirect[pipe->redirect_index].type = HEREDOC;
	pipe->redirect[pipe->redirect_index].val = \
		parse->tokens[i + 1].s;
	pipe->redirect_index++;
}

void	set_key(t_parse *parse, t_pipe *pipe, size_t index)
{
	pipe->cmd[pipe->cmd_index] = parse->tokens[index].s;
	if (pipe->cmd_index == FALSE)
		pipe->cmd_path = pipe->cmd[pipe->cmd_index];
	pipe->cmd_index++;
}

int	set_pipe(t_parse *parse, t_pipe *pipe, size_t *index)
{
	if (malloc_cmd(parse, pipe, *index) == FAILURE)
		return (FAILURE);
	if (malloc_re(parse, pipe, *index) == FAILURE)
		return (FAILURE);
	while (*index < parse->token_count)
	{
		if (parse->tokens[*index].type == PIPE)
		{
			pipe->is_pipe = TRUE;
			(*index)++;
			break ;
		}
		if (parse->tokens[*index].type == KEY)
			set_key(parse, pipe, *index);
		if (parse->tokens[*index].type == REDIRECT)
		{
			set_re(parse, pipe, *index);
			(*index)++;
		}
		(*index)++;
	}
	return (SUCCESS);
}

int	make_pipe(t_parse *parse, t_cmd *cmd)
{
	t_pipe	*pipe;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < cmd->pipe_count)
	{
		pipe = &cmd->pipe[i];
		init_pipe(pipe);
		if (set_pipe(parse, pipe, &j) == FAILURE)
		{
			free_cmd(cmd, i);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}
