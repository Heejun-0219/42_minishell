/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:49:51 by heejunki          #+#    #+#             */
/*   Updated: 2023/07/21 02:43:45 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_valid(char *str)
{
	size_t	i;

	i = 0;
	if (ft_isalpha(str[0]) == FALSE && str[0] != '_')
	{
		return (FALSE);
	}
	while (str[i])
	{
		if (str[i] == '=')
			return (TRUE);
		if (ft_isalnum(str[i]) == FALSE && str[i] != '_')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_node	*get_if_env_exist(t_list *env_list, const char *s)
{
	t_node	*node;
	char	**front;

	front = ft_split(s, '=');
	node = env_list->front;
	while (node)
	{
		if (ft_strncmp(node->content, front[0], ft_strlen(front[0]) + 1) == 0 \
			|| ft_strncmp(node->content, front[0], ft_strlen(front[0]) + 1) == \
			'=')
		{
			free(front[0]);
			free(front[1]);
			free(front);
			return (node);
		}
		node = node->next;
	}
	free(front[0]);
	free(front[1]);
	free(front);
	return (NULL);
}

static void	export_insert(t_info *info, t_pipe *pipe)
{
	size_t	i;
	t_node	*node;

	i = 1;
	while (pipe->cmd[i])
	{
		if (check_valid(pipe->cmd[i]) == FALSE)
		{
			printf("minishell: export: `%s': not a valid identifier\n", \
				pipe->cmd[i]);
			i++;
			continue ;
		}
		node = get_if_env_exist(&(info->env_list), pipe->cmd[i]);
		if (node == NULL)
			ft_lstpush_back(&(info->env_list), ft_strdup(pipe->cmd[i]));
		else
		{
			free(node->content);
			node->content = ft_strdup(pipe->cmd[i]);
		}
		i++;
	}
}

static void	export_no(t_list *env_list)
{
	int	i;

	i = 0;
	while (i < 26)
	{
		export_c(env_list, "acegikmoqsuwyACEGIKMOQSUWY"[i]);
		export_c(env_list, "bdfhjlnprtvxzBDFHJLNPRTVXZ"[i]);
		i++;
	}
	export_c(env_list, '_');
}

int	exe_export(t_parse *parse, t_cmd *cmd, t_info *info, t_pipe *pipe)
{
	(void)parse;
	(void)cmd;
	if (pipe->cmd[1] == NULL)
		export_no(&(info->env_list));
	else
		export_insert(info, pipe);
	if (pipe->exe_in_par == TRUE)
		return (SUCCESS);
	else
		exit(SUCCESS);
}
