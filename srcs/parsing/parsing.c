/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:12:11 by mi                #+#    #+#             */
/*   Updated: 2023/07/22 00:15:41 by heejunki         ###   ########.fr       */
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
	output = ft_malloc((2 * input_length + 1) * sizeof(char));
	if (output == NULL)
		return (NULL);
	process_characters(input, output, &j, input_length);
	output = ft_realloc(output, (j + 1) * sizeof(char));
	output[j] = '\0';
	free(input);
	return (output);
}

t_token	set_token(char *token_str, int index)
{
	t_token	new_token;

	new_token.s = ft_strdup(token_str);
	new_token.token_index = index;
	if (ft_strcmp(token_str, "|") == 0)
		new_token.type = PIPE;
	else if (ft_strcmp(token_str, ">") == 0 || ft_strcmp(token_str, ">>") == 0)
		new_token.type = REDIRECT;
	else if (ft_strcmp(token_str, "<") == 0 || ft_strcmp(token_str, "<<") == 0)
		new_token.type = REDIRECT;
	else
		new_token.type = KEY;
	free(token_str);
	return (new_token);
}

void	while_set_token(t_parse *parse, char **tokens_str, size_t num_tokens)
{
	size_t	token_index;
	size_t	strs_index;

	token_index = 0;
	strs_index = 0;
	while (strs_index < num_tokens)
	{
		if (tokens_str[strs_index][0] == '\0')
		{
			free(tokens_str[strs_index]);
			strs_index++;
			continue ;
		}
		parse->tokens[token_index] = set_token(tokens_str[strs_index], \
		token_index);
		token_index++;
		strs_index++;
	}
	parse->token_count = token_index;
}

int	tokenize_line(t_info *info, t_parse *parse)
{
	char	**tokens_str;
	size_t	num_tokens;

	parse->line = add_space(parse->line);
	tokens_str = split_respect_quote(parse->line, ' ');
	if (tokens_str == NULL)
		return (print_syntax_error());
	if_env_change(info, tokens_str, count_strs(tokens_str));
	if (tokens_str[0][0] == '\0' && count_strs(tokens_str) == 1)
		return (parsing_free(tokens_str));
	tokens_str = remove_quote(tokens_str);
	if (tokens_str == NULL)
		return (print_syntax_error());
	num_tokens = count_strs(tokens_str);
	parse->tokens = ft_malloc(sizeof(t_token) * (num_tokens));
	while_set_token(parse, tokens_str, num_tokens);
	free(tokens_str);
	return (1);
}
