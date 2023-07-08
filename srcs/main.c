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
	// parse | info 환경변수 확인? 

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

int	main(int ac, char **av, char **env)
{
	t_parse	parse;
	t_info	info;
	t_cmd	cmd;
	size_t	line_index;

	init_info(&info, ac, av, env);
	line_index = 0;
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
		add_history(parse.line);
		tokenize_line(&parse);
		parse.line_index = line_index++;
		parse_exe(&parse, &cmd, &info);
		free(parse.line);
	}
	return (SUCCESS);
}
