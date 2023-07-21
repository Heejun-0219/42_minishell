/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:47:58 by heejunki          #+#    #+#             */
/*   Updated: 2023/07/06 14:48:13 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	diff_env_export(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	exe_env(t_parse *parse, t_cmd *cmd, t_info *info, t_pipe *pipe)
{
	t_node	*node;

	(void)parse;
	(void)cmd;
	(void)pipe;
	node = info->env_list.front;
	while (node)
	{
		if (diff_env_export(node->content) == TRUE)
			printf("%s\n", (char *)(node->content));
		node = node->next;
	}
	exit(EXIT_SUCCESS);
}
