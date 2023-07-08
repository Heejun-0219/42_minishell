/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:12:11 by mi                #+#    #+#             */
/*   Updated: 2023/07/08 15:25:37 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	set_token(char *token_str, int index)
{
	t_token	new_token;

	new_token.s = token_str;
	new_token.token_index = index;
	if (strcmp(token_str, "|") == 0)
		new_token.type = PIPE;
	else if (strcmp(token_str, ">") == 0 || strcmp(token_str, ">>") == 0)
		new_token.type = REDIRECT;
	else if (strcmp(token_str, "<") == 0 || strcmp(token_str, "<<") == 0)
		new_token.type = REDIRECT;
	else
		new_token.type = KEY;
	return (new_token);
}

void	tokenize_line(t_parse *parse)
{
	char	**tokens_str;
	size_t	num_tokens;
	size_t	i;

	num_tokens = 0;
	i = 0;
	tokens_str = ft_split(parse->line, ' ');
	for (int i = 0; tokens_str[i] != NULL; i++)
		printf("%s\n", tokens_str[i]);
	num_tokens = count_strs(tokens_str);
	merge_quoted_tokens(tokens_str, num_tokens);
	num_tokens = count_strs(tokens_str);
	for (int i = 0; tokens_str[i] != NULL; i++)
		printf("%s\n", tokens_str[i]);
	printf("num_tokens : %zu\n", num_tokens);
	parse->tokens = ft_malloc(sizeof(t_token) * (num_tokens));
	parse->token_count = num_tokens;
	while (i < num_tokens)
	{
		parse->tokens[i] = set_token(tokens_str[i], i);
		i++;
	}
}
