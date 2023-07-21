/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:45:37 by heejunki          #+#    #+#             */
/*   Updated: 2023/07/21 19:57:01 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_c(t_list *env_list, char c)
{
	t_node	*node;

	node = env_list->front;
	while (node)
	{
		if (ft_strncmp(node->content, &c, 1) == SUCCESS)
			printf("declare -x %s\n", (char *)(node->content));
		node = node->next;
	}
}

char	*get_env_val(char *key, t_info *info)
{
	char	*env_val;
	t_node	*node;

	node = info->env_list.front;
	while (node)
	{
		env_val = node->content;
		if (ft_strncmp(env_val, key, ft_strlen(key)) == 0)
			return (env_val);
		if (node->next == NULL)
			break ;
		node = node->next;
	}
	return (NULL);
}
