/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:12:11 by mi                #+#    #+#             */
/*   Updated: 2023/07/20 23:07:54 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *add_space(char *input)
{
	int input_length = strlen(input);
	int i, j = 0;
	int in_quotes = 0;
	char *output = malloc((2 * input_length + 1) * sizeof(char)); // initial allocation
	if (output == NULL)
	{
		printf("Memory allocation failed\n");
		return NULL;
	}

	for (i = 0; i < input_length; i++)
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			in_quotes = !in_quotes; // toggle quote state
		}
		if (!in_quotes && (input[i] == '<' || input[i] == '>' || input[i] == '|'))
		{
			output[j++] = ' ';
			output[j++] = input[i];
			if (i + 1 < input_length && input[i] == input[i + 1])
			{ // check if next character is the same
				output[j++] = input[i];
				i++; // skip next character
			}
			output[j++] = ' ';
		}
		else
		{
			output[j++] = input[i];
		}
	}
	output = realloc(output, (j + 1) * sizeof(char)); // realloc for null terminator
	output[j] = '\0';							  // Don't forget to null-terminate the new string
	free(input);
	return output;
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
	for (int i = 0; tokens_str[i] != NULL; i++)
		printf("%s\n", tokens_str[i]);
	parse->tokens = ft_malloc(sizeof(t_token) * (num_tokens));
	parse->token_count = num_tokens;
	while (i < num_tokens)
	{
		parse->tokens[i] = set_token(tokens_str[i], i);
		i++;
	}
	return (1);
}