/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:43:14 by heejunki          #+#    #+#             */
/*   Updated: 2023/07/21 22:14:15 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_en(t_cha_env *cv, char **str, int flag)
{
	if (flag == 1)
	{
		free(cv->target);
		free(cv->env);
	}
	else if (flag == 2)
	{
		free(cv->target);
		free(cv->env);
		free(cv->tmp1);
	}
	else if (flag == 3)
	{
		free(cv->env);
		free(cv->tmp1);
		free(cv->token->s);
	}
	free(str[0]);
	free(str[1]);
	free(str);
}

void	free_cmd(t_cmd *cmd, size_t pipe_i)
{
	size_t		i;

	i = 0;
	while (i < pipe_i)
	{
		free(cmd->pipe[i].cmd);
		free(cmd->pipe[i].redirect);
		i++;
	}
	free(cmd->pipe);
	i = 0;
	while (cmd->envp[i])
	{
		free(cmd->envp[i]);
		i++;
	}
	free(cmd->envp);
}

void	free_tokens(t_parse *parse, size_t token_size)
{
	size_t	i;

	i = 0;
	while (i < token_size)
	{
		free(parse->tokens[i].s);
		i++;
	}
	free(parse->tokens);
}

void	free_mini(t_parse *parse, t_cmd *cmd)
{
	free_tokens(parse, parse->token_count);
	free_cmd(cmd, cmd->pipe_count);
}

int	parsing_free(char **tokens_str)
{
	int	i;

	i = 0;
	while (tokens_str[i])
	{
		free(tokens_str[i]);
		i++;
	}
	free(tokens_str);
	return (-1);
}
