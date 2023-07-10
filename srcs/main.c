/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:26:58 by heejunki          #+#    #+#             */
/*   Updated: 2023/07/08 15:54:07 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int null_line(char *line)
{
	size_t index;

	index = 0;
	while (line[index] == ' ')
		index++;
	if (line[index] == '\0')
	{
		free(line);
		return (FAILURE);
	}
	return (SUCCESS);
}

static int memory_parse(t_parse *parse, t_info *info)
{
	size_t	i;

	info->ac = (int) parse->token_count;
	info->av = (char **)malloc(sizeof(char *) * (parse->token_count + 1));
	if (info->av == NULL)
		return (ft_error("malloc error\n", FAILURE));
	i = 0;
	while (i < parse->token_count)
	{
		info->av[i] = ft_strdup(parse->tokens[i].s);
		i++;
	}
	info->av[parse->token_count] = NULL;
	return (SUCCESS);
}

static void	parse_exe(t_parse *parse, t_cmd *cmd, t_info *info)
{
	tokenize_line(parse);
	if (make_cmd_info(parse, cmd, info) == FAILURE)
		return ;
	for (size_t i = 0; i < parse->token_count; i++)
		printf("token[%zu] = %s\n", i, parse->tokens[i].s);
	if (exe_cmd(parse, cmd, info) == FAILURE)
	{
		free_mini(parse, cmd);
		return ;
	}
	if (memory_parse(parse, info) == FAILURE)
		return ;
	free_mini(parse, cmd);
}

// blank
// g_exit_code => parsing
// git commit -m "fix: HOME -> HOME="
int	main(int ac, char **av, char **env)
{
	t_parse	parse;
	t_info	info;
	t_cmd	cmd;

	init_info(&info, ac, av, env);
	while (TRUE)
	{
		init_sig(&info);
		parse.line = readline(PROMPT);
		if (parse.line == NULL)
		{
			ft_lstclear(&info.env_list);
			printf("\x1b[1A\033[11Cexit\n");
			break ;
		}
		if (parse.line[0] == '\0')
		{
			free(parse.line);
			continue ;
		}
		if (null_line(parse.line) == FAILURE)
			continue;
		add_history(parse.line);
		parse_exe(&parse, &cmd, &info);
		free(parse.line);
	}
	return (SUCCESS);
}
