/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:52:35 by heejunki          #+#    #+#             */
/*   Updated: 2023/07/11 15:54:05 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	backslash_to_space(t_parse *parse, size_t i)
{
	size_t	j;
	char	*tmp;

	while (i < parse->token_count)
	{
		if (parse->tokens[i].type == KEY)
		{
			j = 0;
			while (j < strlen(parse->tokens[i].s))
			{
				if (parse->tokens[i].s[j] == '\\' && \
					parse->tokens[i].s[j + 1] == '\\')
				{
					tmp = ft_strdup(parse->tokens[i].s + 1);
					free(parse->tokens[i].s);
					parse->tokens[i].s = tmp;
					j++;
				}
				j++;
			}
		}
		i++;
	}
}

static int	check_pipe(t_parse *parse, t_cha_env *syn)
{
	if (syn->token_index == 0 || syn->token_index == parse->token_count - 1)
	{
		g_exit_code = 258;
		return (ft_error("Syntax Error: parse error", FAILURE));
	}
	else
	{
		if (parse->tokens[syn->token_index - 1].type == PIPE
			|| parse->tokens[syn->token_index + 1].type == PIPE)
		{
			g_exit_code = 258;
			return (ft_error("Syntax Error: parse error", FAILURE));
		}
	}
	return (SUCCESS);
}

static int	check_op(t_parse *parse, t_cha_env *syn)
{
	if (ft_strncmp(parse->tokens[syn->token_index].s, "||", 2) == SUCCESS)
	{
		g_exit_code = 258;
		return (ft_error("Syntax Error: parse error ||", FAILURE));
	}
	else if (ft_strncmp(parse->tokens[syn->token_index].s, "<<<", 3) == SUCCESS)
	{
		g_exit_code = 258;
		return (ft_error("Syntax Error: parse error <<<", FAILURE));
	}
	else if (ft_strncmp(parse->tokens[syn->token_index].s, ">>>", 3) == SUCCESS)
	{
		g_exit_code = 258;
		return (ft_error("Syntax Error: parse error >>>", FAILURE));
	}
	else if (ft_strncmp(parse->tokens[syn->token_index].s, "&", 1) == SUCCESS \
		|| ft_strncmp(parse->tokens[syn->token_index].s, ";", 1) == SUCCESS)
	{
		g_exit_code = 258;
		return (ft_error("Syntax Error: parse error & or ;", FAILURE));
	}
	return (SUCCESS);
}

static int	check_redirect(t_parse *parse, t_cha_env *syn)
{
	if (syn->token_index == parse->token_count - 1)
	{
		g_exit_code = 258;
		return (ft_error("Syntax Error: No word after REDIRECT", FAILURE));
	}
	else
	{
		if (parse->tokens[syn->token_index + 1].type != KEY)
		{
			g_exit_code = 258;
			return (ft_error("Syntax Error: No word after REDIRECT", FAILURE));
		}
	}
	return (SUCCESS);
}

int	syntax_error(t_parse *parse)
{
	t_cha_env	*syn;

	syn = (t_cha_env *)malloc(sizeof(t_cha_env));
	syn->token_index = 0;
	while (syn->token_index < parse->token_count)
	{
		if (check_op(parse, syn) == FAILURE)
			return (FAILURE);
		else if (parse->tokens[syn->token_index].type == PIPE)
		{
			if (check_pipe(parse, syn) == FAILURE)
				return (FAILURE);
		}
		else if (parse->tokens[syn->token_index].type == REDIRECT)
		{
			if (check_redirect(parse, syn) == FAILURE)
				return (FAILURE);
		}
		syn->token_index++;
	}
	free(syn);
	return (SUCCESS);
}
