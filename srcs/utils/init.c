/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:28:26 by heejunki          #+#    #+#             */
/*   Updated: 2023/07/21 02:20:49 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code;

int	token_to_cha(t_cha_env *cha_env, char *line)
{
	t_token	*token;

	token = (t_token *) malloc(sizeof(t_token));
	if (token == NULL)
		return (ft_error("malloc error\n", FAILURE));
	token->s = ft_strdup(line);
	cha_env->token = token;
	cha_env->string_index = 0;
	return (SUCCESS);
}

void	init_env_list(t_info *info, char **env)
{
	size_t	i;

	i = 0;
	info->env_list = ft_lst_init();
	while (env[i] != NULL)
	{
		ft_lstpush_back(&info->env_list, ft_strdup(env[i]));
		i++;
	}
}

void	init_info(t_info *info, int ac, char **av, char **env)
{
	g_exit_code = 0;
	info->ac = ac;
	info->av = av;
	info->env = env;
	tcgetattr(STDIN_FILENO, &info->term_back);
	init_env_list(info, env);
	info->last_c = 0;
	info->last_v = NULL;
}

int	init_cmd(t_parse *parse, t_cmd *cmd, t_info *info)
{
	if (get_path_env(parse, cmd, info) == FAILURE)
		return (FAILURE);
	cmd->pipe_index = 0;
	cmd->pre_pipe_fd = -1;
	cmd->pipe = (t_pipe *)malloc(sizeof(t_pipe) * cmd->pipe_count);
	if (cmd->pipe == NULL)
	{
		free(cmd->envp);
		free_tokens(parse, parse->token_count);
		return (ft_error("malloc error\n", FAILURE));
	}
	return (SUCCESS);
}

void	init_pipe(t_pipe *pipe)
{
	pipe->cmd_path = NULL;
	pipe->cmd = NULL;
	pipe->cmd_index = 0;
	pipe->redirect = NULL;
	pipe->redirect_index = 0;
	pipe->is_pipe = FALSE;
	pipe->in_fd = FAILURE;
	pipe->out_fd = FAILURE;
	pipe->exe_in_par = FALSE;
}
