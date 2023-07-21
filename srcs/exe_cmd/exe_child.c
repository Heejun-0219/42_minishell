/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_child.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:46:58 by heejunki          #+#    #+#             */
/*   Updated: 2023/07/21 19:29:55 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_dir(const char *path)
{
	DIR	*dir;

	if (path == NULL)
	{
		printf("Error: path is null\n");
		exit(126);
	}
	dir = opendir(path);
	if (dir != NULL)
	{
		printf("minishell: %s: is a directory\n", path);
		exit(126);
	}
}

static char	*get_path(t_pipe *pipe, char *envp)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(envp, "/");
	if (tmp == NULL)
		exit(EXIT_FAILURE);
	path = ft_strjoin(tmp, pipe->cmd_path);
	if (path == NULL)
	{
		free(tmp);
		exit(EXIT_FAILURE);
	}
	free(tmp);
	return (path);
}

static int	check_access_cmd(t_cmd *cmd, t_pipe *pipe)
{
	size_t	i;
	char	*path;

	i = 0;
	path = pipe->cmd_path;
	check_dir(path);
	if (path == NULL || access(path, X_OK) == SUCCESS)
		return (SUCCESS);
	if (path[0] == '\0')
		return (FAILURE);
	while (cmd->envp[i])
	{
		path = get_path(pipe, cmd->envp[i]);
		if (access(path, X_OK) == SUCCESS)
		{
			pipe->cmd_path = path;
			return (SUCCESS);
		}
		free(path);
		i++;
	}
	return (FAILURE);
}

static char	**set_envp(t_list *envp_list)
{
	char	**envp;
	size_t	count;
	t_node	*node;

	count = 0;
	node = envp_list->front;
	while (node->next != NULL)
	{
		count++;
		node = node->next;
	}
	envp = (char **)malloc(sizeof(char *) * (count + 2));
	if (envp == NULL)
		exit(ft_error("envp malloc failed\n", EXIT_FAILURE));
	count = 0;
	node = envp_list->front;
	while (node != NULL)
	{
		envp[count] = (char *)node->content;
		node = node->next;
		count++;
	}
	envp[count] = NULL;
	return (envp);
}

void	exe_child(t_info *info, t_parse *parse, t_cmd *cmd, t_pipe *pipe)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (check_builtin(pipe) == FALSE && \
		check_access_cmd(cmd, pipe) == FAILURE)
	{
		printf("minishell: %s: command not found\n", pipe->cmd[0]);
		free_mini(parse, cmd);
		exit(127);
	}
	else
	{
		set_fd(cmd, pipe);
		if (pipe->cmd_path == NULL)
			exit(EXIT_SUCCESS);
		if (check_builtin(pipe) == TRUE)
			exe_builtin(parse, cmd, info, pipe);
		else
			execve(pipe->cmd_path, pipe->cmd, set_envp(&info->env_list));
	}
}
