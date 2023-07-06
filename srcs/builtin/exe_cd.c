/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:46:33 by heejunki          #+#    #+#             */
/*   Updated: 2023/07/06 16:59:06 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_val(char *key, t_info *info)
{
	char	*env_val;
	t_node	*node;

	node = info->env_list.front;
	while (node)
	{
		env_val = node->content;
		if (ft_strncmp(key, env_val, ft_strlen(key)) == 0)
			return (env_val);
		node = node->next;
	}
	return (NULL);
}

int	exe_cd(t_pipe *pipe, t_info *info)
{
	char	*path;

	path = pipe->cmd[1];
	if (path == NULL)
	{
		if (pipe->builtin == TRUE)
			return (SUCCESS);
		else
			exit(EXIT_SUCCESS);
	}
	if (path[0] == '~')
	{
		path = ft_strjoin(get_env_val("HOME", info), path + 1);
		path = ft_split(path, '=')[1];
		printf("%s\n", path);
	}
	if (chdir(path) == FAILURE)
	{
		g_exit_code = 1;
		if (pipe->builtin == TRUE)
		{
			printf("minishell: cd: %s: %s\n", path, strerror(errno));
			return (ft_perror(SUCCESS));
		}
		else
			exit(EXIT_SUCCESS);
	}
	if (pipe->builtin == TRUE)
		return (SUCCESS);
	else
		exit(EXIT_SUCCESS);
}
