/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:30:54 by heejunki          #+#    #+#             */
/*   Updated: 2023/07/20 22:50:13 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	malloc_cmd(t_parse *parse, t_pipe *pipe, size_t index)
{
	size_t	i;
	size_t	token_count;

	i = index;
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
	pipe->cmd = (char **)ft_calloc(token_count + 1, sizeof(char *));
	if (pipe->cmd == NULL)
		return (ft_error("malloc error\n", FAILURE));
	return (SUCCESS);
}

int	malloc_re(t_parse *parse, t_pipe *pipe, size_t index)
{
	size_t	i;
	size_t	re_count;

	i = index;
	re_count = 0;
	while (i < parse->token_count)
	{
		if (parse->tokens[i].type == PIPE)
			break ;
		if (parse->tokens[i].type == REDIRECT)
			re_count++;
		i++;
	}
	pipe->redirect = (t_redirect *)ft_calloc(re_count + 1, sizeof(t_redirect));
	if (pipe->redirect == NULL)
		return (ft_error("malloc error\n", FAILURE));
	return (SUCCESS);
}

void	get_exe_count(t_parse *parse, t_cmd *cmd)
{
	size_t	i;

	i = 0;
	cmd->pipe_count = 1;
	while (i < parse->token_count)
	{
		if (parse->tokens[i].type == PIPE)
			cmd->pipe_count++;
		i++;
	}
}

int	get_path_env(t_parse *parse, t_cmd *cmd, t_info *info)
{
	char	*path;
	t_node	*node;

	node = info->env_list.front;
	while (node && ft_strncmp(node->content, "PATH=", 5) != 0)
		node = node->next;
	if (node == NULL)
	{
		cmd->envp = (char **)malloc(sizeof(char *) * 2);
		if (cmd->envp == NULL)
			return (ft_error("malloc error\n", FAILURE));
		return (SUCCESS);
	}
	path = node->content + 5;
	cmd->envp = ft_split(path, ':');
	if (cmd->envp == NULL)
	{
		free_tokens(parse, parse->token_count);
		return (ft_error("malloc error\n", FAILURE));
	}
	return (SUCCESS);
}

int	make_cmd_info(t_parse *parse, t_cmd *cmd, t_info *info)
{
	if (syntax_error(parse) == FAILURE)
	{
		free_tokens(parse, parse->token_count);
		return (FAILURE);
	}
	backslash_to_space(parse, 0);
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
