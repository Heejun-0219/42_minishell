/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:50:47 by heejunki          #+#    #+#             */
/*   Updated: 2023/07/11 15:51:34 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	change_env(t_info *info, t_cha_env *cv)
{
	cv->start = cv->string_index;
	while (ft_isalnum(cv->token->s[cv->string_index + 1]) \
		|| cv->token->s[cv->string_index + 1] == '_' \
		|| cv->token->s[cv->string_index + 1] == '-')
		cv->string_index++;
	cv->target_len = cv->string_index - cv->start;
	cv->target = (char *) malloc(sizeof(char) * (cv->target_len + 1));
	if (cv->target == NULL)
		return (ft_error("malloc error\n", FAILURE));
	ft_strlcpy(cv->target, &cv->token->s[cv->start + 1], cv->target_len + 1);
	cv->env = ft_strjoin(cv->target, "=");
	if (cv->env == NULL)
	{
		free(cv->target);
		return (ft_error("malloc error\n", FAILURE));
	}
	free(cv->target);
	if (get_env_val(cv->env, info) != NULL)
		return (TRUE);
	free(cv->env);
	return (FALSE);
}

static int	add_env(t_info *info, t_cha_env *cv)
{
	cv->token->s[cv->start] = '\0';
	cv->env_len = ft_strlen(ft_split(get_env_val(cv->env, info), '=')[1]);
	cv->tmp1 = ft_strjoin(cv->token->s, \
		ft_split(get_env_val(cv->env, info), '=')[1]);
	if (cv->tmp1 == NULL)
	{
		free(cv->target);
		free(cv->env);
		return (ft_error("change env error\n", FAILURE));
	}
	cv->tmp2 = ft_strjoin(cv->tmp1, &cv->token->s[cv->string_index + 1]);
	if (cv->tmp2 == NULL)
	{
		free(cv->target);
		free(cv->env);
		free(cv->tmp1);
		return (ft_error("change env error\n", FAILURE));
	}
	free(cv->env);
	free(cv->tmp1);
	cv->token->s = cv->tmp2;
	return (SUCCESS);
}

static int	is_env(t_info *info, t_cha_env *cv)
{
	if (cv->token->s[cv->string_index] == '$' && \
		ft_isalpha(cv->token->s[cv->string_index + 1]))
	{
		if (change_env(info, cv) == TRUE)
		{
			if (add_env(info, cv) == FAILURE)
				return (FAILURE);
			cv->string_index = cv->start + cv->env_len - 1;
		}
		else
		{
			ft_strlcpy(&cv->token->s[cv->start], \
				&cv->token->s[cv->string_index + 1], \
				ft_strlen(cv->token->s) + 1);
			cv->string_index -= cv->target_len + 1;
		}
	}
	else if (cv->token->s[cv->string_index] == '$')
		return (change_special_env(info, cv));
	else if (cv->token->s[cv->string_index] == '~')
		if (change_abs(info, cv) == FAILURE)
			return (FAILURE);
	return (SUCCESS);
}

int	if_env_change(t_info *info, t_parse *parse)
{
	t_cha_env	*cha_env;

	cha_env = (t_cha_env *) malloc(sizeof(t_cha_env));
	cha_env->token_index = 0;
	while (cha_env->token_index < parse->token_count)
	{
		cha_env->token = &parse->tokens[cha_env->token_index];
		cha_env->string_index = 0;
		while (cha_env->token->s[cha_env->string_index])
		{
			if (check_here(cha_env->token->s[cha_env->string_index], \
			cha_env->token->s[cha_env->string_index + 1]) == TRUE)
			{
				cha_env->token_index++;
				break ;
			}
			if (is_env(info, cha_env) == FAILURE)
				return (FAILURE);
			cha_env->string_index++;
		}
		cha_env->token_index++;
	}
	return (SUCCESS);
}
