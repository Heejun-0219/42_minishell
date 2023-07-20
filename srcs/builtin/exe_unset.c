/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:50:27 by heejunki          #+#    #+#             */
/*   Updated: 2023/07/20 15:28:24 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	del_env_val(t_info *info, t_pipe *pipe)
{
	size_t	i;
	t_node	*node;

	i = 1;
	while (pipe->cmd[i])
	{
		if (check_valid(pipe->cmd[i]) == FALSE)
		{
			printf("minishell: unset: `%s': not a valid identifier\n", \
				pipe->cmd[i]);
			i++;
			continue ;
		}
		node = get_if_env_exist(&(info->env_list), pipe->cmd[i]);
		if (node != NULL)
			ft_lstdel_node(&(info->env_list), node);
		i++;
	}
}

int	exe_unset(t_info *info, t_pipe *pipe)
{
	if (pipe->cmd[1] == NULL)
	{
		if (pipe->exe_in_par == TRUE)
			return (SUCCESS);
		else
			exit(EXIT_SUCCESS);
	}
	else
	{
		del_env_val(info, pipe);
	}
	if (pipe->exe_in_par == TRUE)
		return (SUCCESS);
	else
		exit(EXIT_SUCCESS);
}
