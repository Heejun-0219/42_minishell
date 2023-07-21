/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:50:47 by heejunki          #+#    #+#             */
/*   Updated: 2023/07/21 19:56:50 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	**str;

	str = ft_split(get_env_val(cv->env, info), '=');
	cv->token->s[cv->start] = '\0';
	cv->env_len = ft_strlen(str[1]);
	cv->tmp1 = ft_strjoin(cv->token->s, str[1]);
	if (cv->tmp1 == NULL)
	{
		free_en(cv, str, 1);
		return (ft_error("change env error\n", FAILURE));
	}
	cv->tmp2 = ft_strjoin(cv->tmp1, &cv->token->s[cv->string_index + 1]);
	if (cv->tmp2 == NULL)
	{
		free_en(cv, str, 2);
		return (ft_error("change env error\n", FAILURE));
	}
	free_en(cv, str, 3);
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

static int	go_env(t_cha_env *cha_env, t_info *info, int s_quote)
{
	while (cha_env->token->s[cha_env->string_index])
	{
		if (cha_env->token->s[cha_env->string_index] == '\'')
			s_quote *= -1;
		if (s_quote == 1)
		{
			if (check_here(cha_env->token->s[cha_env->string_index], \
			cha_env->token->s[cha_env->string_index + 1]) == TRUE)
				break ;
			if (is_env(info, cha_env) == FAILURE)
				return (FAILURE);
		}
		cha_env->string_index++;
	}
	return (SUCCESS);
}

int	if_env_change(t_info *info, char **line, size_t token_count)
{
	t_cha_env	*cha_env;
	int			s_quote;

	cha_env = (t_cha_env *) malloc(sizeof(t_cha_env));
	cha_env->token_index = 0;
	while (cha_env->token_index < token_count)
	{
		s_quote = 1;
		if (token_to_cha(cha_env, line[cha_env->token_index]) == FAILURE)
			return (FAILURE);
		if (go_env(cha_env, info, s_quote) == FAILURE)
			return (FAILURE);
		free(line[cha_env->token_index]);
		line[cha_env->token_index] = cha_env->token->s;
		cha_env->token_index++;
		free(cha_env->token);
	}
	free(cha_env);
	return (SUCCESS);
}
