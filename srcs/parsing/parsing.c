/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:12:11 by mi                #+#    #+#             */
/*   Updated: 2023/07/20 23:24:28 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_characters(char *input, char *output, int *j, int input_length)
{
	int	i;
	int	in_quotes;

	i = 0;
	in_quotes = 0;
	while (i < input_length)
	{
		if (input[i] == '"' || input[i] == '\'')
			in_quotes = !in_quotes;
		if (!in_quotes && (input[i] == '<' || input[i] == '>' || \
		input[i] == '|'))
		{
			output[(*j)++] = ' ';
			output[(*j)++] = input[i];
			if (i + 1 < input_length && input[i] == input[i + 1])
			{
				output[(*j)++] = input[i];
				i++;
			}
			output[(*j)++] = ' ';
		}
		else
			output[(*j)++] = input[i];
		i++;
	}
}

char	*add_space(char *input)
{
	int		input_length;
	int		j;
	char	*output;

	j = 0;
	input_length = ft_strlen(input);
	output = malloc((2 * input_length + 1) * sizeof(char));
	if (output == NULL)
		return (NULL);
	process_characters(input, output, &j, input_length);
	output = realloc(output, (j + 1) * sizeof(char));
	output[j] = '\0';
	free(input);
	return (output);
}

t_token	set_token(char *token_str, int index)
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

int	tokenize_line(t_info *info, t_parse *parse)
{
	char	**tokens_str;
	size_t	num_tokens;
	size_t	i;

	num_tokens = 0;
	i = 0;
	parse->line = add_space(parse->line);
	tokens_str = split_respect_quote(parse->line, ' ');
	if (tokens_str == NULL)
		return (-1);
	if_env_change(info, tokens_str, count_strs(tokens_str));
	tokens_str = remove_quote(tokens_str);
	num_tokens = count_strs(tokens_str);
	parse->tokens = ft_malloc(sizeof(t_token) * (num_tokens));
	parse->token_count = num_tokens;
	while (i < num_tokens)
	{
		parse->tokens[i] = set_token(tokens_str[i], i);
		i++;
	}
	return (1);
}
