/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:46:20 by heejunki          #+#    #+#             */
/*   Updated: 2023/07/21 21:16:03 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin(t_pipe *pipe)
{
	if (pipe->cmd_path == NULL)
		return (FALSE);
	if (ft_strncmp(pipe->cmd[0], "cd", 3) == SUCCESS)
		return (TRUE);
	if (ft_strncmp(pipe->cmd[0], "echo", 5) == SUCCESS)
		return (TRUE);
	if (ft_strncmp(pipe->cmd[0], "env", 4) == SUCCESS)
		return (TRUE);
	if (ft_strncmp(pipe->cmd[0], "exit", 5) == SUCCESS)
		return (TRUE);
	if (ft_strncmp(pipe->cmd[0], "export", 7) == SUCCESS)
		return (TRUE);
	if (ft_strncmp(pipe->cmd[0], "pwd", 4) == SUCCESS)
		return (TRUE);
	if (ft_strncmp(pipe->cmd[0], "unset", 6) == SUCCESS)
		return (TRUE);
	return (FALSE);
}

int	check_builtin_parent(t_cmd *cmd, t_pipe *pipe)
{
	if (cmd->pipe_index != FALSE || pipe->is_pipe == TRUE)
		return (FALSE);
	if (pipe->cmd_path == NULL)
		return (FALSE);
	if (ft_strncmp(pipe->cmd[0], "cd", 3) == SUCCESS)
		return (TRUE);
	if (ft_strncmp(pipe->cmd[0], "exit", 5) == SUCCESS)
		return (TRUE);
	if (ft_strncmp(pipe->cmd[0], "export", 7) == SUCCESS)
		return (TRUE);
	if (ft_strncmp(pipe->cmd[0], "unset", 6) == SUCCESS)
		return (TRUE);
	return (FALSE);
}

int	exe_builtin(t_parse *parse, t_cmd *cmd, t_info *info, t_pipe *pipe)
{
	if (ft_strncmp(pipe->cmd[0], "cd", 3) == SUCCESS)
		return (exe_cd(pipe));
	if (ft_strncmp(pipe->cmd[0], "echo", 5) == SUCCESS)
		return (exe_echo(pipe));
	if (ft_strncmp(pipe->cmd[0], "env", 4) == SUCCESS)
		return (exe_env(parse, cmd, info, pipe));
	if (ft_strncmp(pipe->cmd[0], "exit", 5) == SUCCESS)
		return (exe_exit(parse, cmd, info, pipe));
	if (ft_strncmp(pipe->cmd[0], "export", 7) == SUCCESS)
		return (exe_export(parse, cmd, info, pipe));
	if (ft_strncmp(pipe->cmd[0], "pwd", 4) == SUCCESS)
		return (exe_pwd());
	if (ft_strncmp(pipe->cmd[0], "unset", 6) == SUCCESS)
		return (exe_unset(info, pipe));
	return (SUCCESS);
}

int	exe_builtin_parent(t_parse *parse, t_cmd *cmd, t_info *info, t_pipe *pipe)
{
	pipe->exe_in_par = TRUE;
	if (ft_strncmp(pipe->cmd[0], "cd", 3) == SUCCESS)
		return (exe_cd(pipe));
	if (ft_strncmp(pipe->cmd[0], "exit", 5) == SUCCESS)
		return (exe_exit(parse, cmd, info, pipe));
	if (ft_strncmp(pipe->cmd[0], "export", 7) == SUCCESS)
		return (exe_export(parse, cmd, info, pipe));
	if (ft_strncmp(pipe->cmd[0], "unset", 6) == SUCCESS)
		return (exe_unset(info, pipe));
	return (SUCCESS);
}
