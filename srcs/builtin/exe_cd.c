/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:46:33 by heejunki          #+#    #+#             */
/*   Updated: 2023/07/20 14:34:42 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	home_cd(t_pipe *pipe, t_info *info)
{
	if (pipe->builtin == TRUE)
	{
		if (chdir(ft_split(get_env_val("HOME=", info), '=')[1]) == FAILURE)
			return (ft_perror(SUCCESS));
		return (SUCCESS);
	}
	else
		exit(EXIT_SUCCESS);
}

int	exe_cd(t_pipe *pipe, t_info *info)
{
	char	*path;

	path = pipe->cmd[1];
	if (path == NULL)
		return (home_cd(pipe, info));
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
