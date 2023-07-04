/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 23:41:24 by mi                #+#    #+#             */
/*   Updated: 2023/07/05 02:17:54 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t get_array_size(char **array)
{
	size_t count = 0;
	while (array[count] != NULL)
		count++;
	return count;
}

static t_token	set_token(t_parse *parse, char *token_str, int index)
{
	t_token new_token;
	
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

/*
따옴표가 포함된 토큰 병합
ex) grep "hello world" file.txt
split ->
```
grep
"hello
world"
file.txt
```

merge ->
```
grep
"hello world"
file.txt
```
*/
void merge_quoted_tokens(char **tokens_str) 
{
	size_t i;
	size_t j;
	size_t array_size;
	int inside_quotes;

	i = 0;
	inside_quotes = 0;
	while (tokens_str[i] != NULL)
	{
		if (tokens_str[i][0] == '\"' && !inside_quotes)
		{
			inside_quotes = 1;
			j = i + 1;
			while (tokens_str[j] != NULL && tokens_str[j][strlen(tokens_str[j]) - 1] != '\"')
			{
				strcat(tokens_str[i], " ");
				strcat(tokens_str[i], tokens_str[j]);
				free(tokens_str[j]);
				j++;
			}
			if (tokens_str[j] != NULL && tokens_str[j][strlen(tokens_str[j]) - 1] == '\"')
			{
				strcat(tokens_str[i], " ");
				strcat(tokens_str[i], tokens_str[j]);
				free(tokens_str[j]);
			}
			array_size = sizeof(char *) * (get_array_size(tokens_str) - j);
			memmove(&tokens_str[i + 1], &tokens_str[j + 1], array_size);
		}
		i++;
	}
}

void tokenize_line(t_parse *parse) // 라인을 쪼개서, 토큰화 시킴
{
	char **tokens_str;
	size_t num_tokens;
	size_t i;

	num_tokens = 0;
	i = 0;
	tokens_str = ft_split(parse->line, " "); // TODO : 나중에 free 해줘야함
	merge_quoted_tokens(tokens_str);
	while (tokens_str[num_tokens] != NULL)
		num_tokens++;														   // 토큰 개수 세기
	parse->tokens = ft_realloc(parse->tokens, sizeof(t_token) * (num_tokens)); // 토큰 개수만큼 메모리 할당
	parse->token_count = num_tokens;
	while (i < num_tokens)
	{
		parse->tokens[i] = set_token(parse, tokens_str[i], i); // 각각 토큰 타입, 토큰 인덱스, 토큰 문자열 설정 후 토큰 배열에 넣기
		i++;
	}
}
