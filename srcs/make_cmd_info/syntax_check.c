#include "minishell.h"

static int check_pipe(t_parse *parse, t_cha_env *syn)
{
	if (syn->token_index == 0 || syn->token_index == syn->token_index - 1)
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

static int check_op(t_parse *parse, t_cha_env *syn)
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

static int check_redirect(t_parse *parse, t_cha_env *syn)
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

int syntax_error(t_parse *parse)
{
	t_cha_env *syn;

	syn = (t_cha_env *)malloc(sizeof(t_cha_env));
	syn->token_index = 0;
	printf("1\n");
	while (syn->token_index < parse->token_count)
	{
		printf("parse->tokens[syn->token_index].type : %d\n", parse->tokens[syn->token_index].type);
		if (check_op(parse, syn) == FAILURE)
			return (FAILURE);
		else if (parse->tokens[syn->token_index].type == PIPE)
		{
			printf("2\n");
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
