/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:16:42 by mi                #+#    #+#             */
/*   Updated: 2023/07/08 15:33:11 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != NULL)
		i++;
	return (i);
}

/*
void parsed_constructor_free(t_parse *parse)
{
	if (parse->tokens != NULL)
		free(parse->tokens);
	if (parse->line != NULL)
	{
		while (parse->line[parse->line_count] != NULL)
			free(parse->line[parse->line_count++]);
	}
}
*/