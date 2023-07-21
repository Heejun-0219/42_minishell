/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:26:58 by heejunki          #+#    #+#             */
/*   Updated: 2023/07/22 00:27:26 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	null_line(char *line)
{
	size_t	index;

	index = 0;
	while (line[index] == ' ')
		index++;
	if (line[index] == '\0')
	{
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	memory_parse(t_parse *parse, t_info *info)
{
	size_t	i;

	if (info->last_c != 0)
	{
		i = 0;
		while ((int)i < info->last_c)
		{
			free(info->last_v[i]);
			i++;
		}
		free(info->last_v);
	}
	info->last_c = (int) parse->token_count;
	info->last_v = (char **)malloc(sizeof(char *) * (parse->token_count + 1));
	if (info->last_v == NULL)
		return (ft_error("malloc error\n", FAILURE));
	i = 0;
	while (i < parse->token_count)
	{
		info->last_v[i] = ft_strdup(parse->tokens[i].s);
		i++;
	}
	info->last_v[parse->token_count] = NULL;
	return (SUCCESS);
}

static void	parse_exe(t_parse *parse, t_cmd *cmd, t_info *info)
{
	int	tmp;

	tmp = tokenize_line(info, parse);
	if (tmp == -1)
		return ;
	if (make_cmd_info(parse, cmd, info) == FAILURE)
		return ;
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
		if (parse.line[0] == '\0' || null_line(parse.line) == FAILURE)
		{
			free(parse.line);
			continue ;
		}
		add_history(parse.line);
		parse_exe(&parse, &cmd, &info);
		free(parse.line);
	}
	return (SUCCESS);
}
