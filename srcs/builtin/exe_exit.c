/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:48:15 by heejunki          #+#    #+#             */
/*   Updated: 2023/07/21 22:07:36 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_exit(t_cmd *cmd)
{
	printf("exit\n");
	printf("minishell: exit: %s: numeric argument required\n", \
		cmd->pipe[cmd->pipe_index].cmd[1]);
	exit(255);
}

static void	exit_option(t_cmd *cmd)
{
	int	i;
	int	print_operator;

	print_operator = FALSE;
	i = 0;
	if (cmd->pipe[cmd->pipe_index].cmd[1][0] == '-' \
		|| cmd->pipe[cmd->pipe_index].cmd[1][0] == '+')
	{
		print_operator = TRUE;
		i++;
	}
	while (cmd->pipe[cmd->pipe_index].cmd[1][i])
	{
		if (ft_isdigit(cmd->pipe[cmd->pipe_index].cmd[1][i]) == FALSE)
		{
			print_exit(cmd);
		}
		i++;
	}
	if (i == 1 && print_operator == TRUE)
	{
		print_exit(cmd);
	}
}

static void	exit_no_option(t_parse *parse, t_cmd *cmd, \
	t_info *info, t_pipe *pipe)
{
	if (cmd->pipe[cmd->pipe_index].cmd[1] == NULL)
	{
		ft_lstclear(&info->env_list);
		if (pipe->exe_in_par == TRUE)
			printf("exit\n");
		free_mini(parse, cmd);
		exit(EXIT_SUCCESS);
	}
}

int	exe_exit(t_parse *parse, t_cmd *cmd, t_info *info, t_pipe *pipe)
{
	int	exit_val;

	exit_no_option(parse, cmd, info, pipe);
	if (cmd->pipe[cmd->pipe_index].cmd[2] != NULL)
	{
		printf("minishell: exit: too many arguments\n");
		g_exit_code = 1;
		if (pipe->exe_in_par == TRUE)
			return (SUCCESS);
		exit(1);
	}
	exit_option(cmd);
	exit_val = ft_atoi(cmd->pipe[cmd->pipe_index].cmd[1]);
	if (exit_val == 255 && ft_strcmp(cmd->pipe[cmd->pipe_index].cmd[1], "255"))
	{
		printf("minishell: exit: %s: numeric argument required\n", \
			cmd->pipe[cmd->pipe_index].cmd[1]);
		exit(255);
	}
	ft_lstclear(&info->env_list);
	free_mini(parse, cmd);
	exit(exit_val);
}
