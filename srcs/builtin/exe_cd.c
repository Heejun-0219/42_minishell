/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:46:33 by heejunki          #+#    #+#             */
/*   Updated: 2023/07/06 14:47:37 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exe_cd(t_pipe *pipe)
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
