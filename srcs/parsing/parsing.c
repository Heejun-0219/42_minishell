/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 23:41:24 by mi                #+#    #+#             */
/*   Updated: 2023/07/06 03:26:16 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	set_token(char *token_str, int index)
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
// //TODO : 따옴표의 갯수가 홀수일 때 전처리 필요!
// void merge_quoted_tokens(char **tokens_str)
// {
// 	size_t i;
// 	size_t j;
// 	size_t array_size;
// 	int inside;

// 	i = 0;
// 	inside = 0;
// 	while (tokens_str[i] != NULL)
// 	{
// 		if ((tokens_str[i][0] == '\"' || tokens_str[i][0] == '\'')&& !inside)
// 		{
// 			inside = 1;
// 			j = i + 1;
// 			while (tokens_str[j] != NULL && !ends_with_quote(tokens_str[j]))
// 			{
// 				merge_and_free_tokens(&tokens_str[i], tokens_str[j]);
// 				j++;
// 			}
// 			if (ends_with_quote(tokens_str[j]))
// 				merge_and_free_tokens(&tokens_str[i], tokens_str[j]);
// 			array_size = sizeof(char *) * (get_array_size(tokens_str) - j);
// 			memmove(&tokens_str[i + 1], &tokens_str[j + 1], array_size);
// 		}
// 		i++;
// 	}
// }

// void merge_quoted_tokens(char **tokens_str)
// {
// 	size_t i;
// 	size_t j;
// 	size_t array_size;
// 	int inside_double;
// 	int inside_single;

// 	i = 0;
// 	inside_double = 0;
// 	inside_single = 0;
// 	while (tokens_str[i] != NULL)
// 	{
// 		if (tokens_str[i][0] == '\"' && !inside_single)
// 			inside_double = !inside_double;
// 		if (tokens_str[i][0] == '\'' && !inside_double)
// 			inside_single = !inside_single;
// 		if (inside_double || inside_single)
// 		{
// 			j = i + 1;
// 			while (tokens_str[j] != NULL && !is_end_of_quote_scope(tokens_str[j], inside_double, inside_single))
// 				merge_and_free_tokens(&tokens_str[i], tokens_str[j++]);
// 			if (is_end_of_quote_scope(tokens_str[j], inside_double, inside_single))
// 			{
// 				merge_and_free_tokens(&tokens_str[i], tokens_str[j]);
// 				inside_double = ft_not(inside_double);	// 1 -> 0, 0 -> 1
// 				inside_single = ft_not(inside_single);	// 1 -> 0, 0 -> 1
// 			}
// 			array_size = sizeof(char *) * (get_array_size(tokens_str) - j);
// 			memmove(&tokens_str[i + 1], &tokens_str[j + 1], array_size);
// 		}
// 		i++;
// 	}
// }

void tokenize_line(t_parse *parse) // 라인을 쪼개서, 토큰화 시킴
{
	char **tokens_str;
	size_t num_tokens;
	size_t i;

	num_tokens = 0;
	i = 0;
	tokens_str = ft_split(parse->line, ' '); // TODO : 나중에 free 해줘야함
	for (int i = 0; tokens_str[i] != NULL; i++)
		printf("%s\n", tokens_str[i]);
	merge_quoted_tokens(tokens_str);
	for (int i = 0; tokens_str[i] != NULL; i++)
		printf("%s\n", tokens_str[i]);
	while (tokens_str[num_tokens] != NULL)
		num_tokens++;													   // 토큰 개수 세기
	printf("num_tokens : %zu\n", num_tokens);
	parse->tokens = ft_malloc(sizeof(t_token) * (num_tokens)); // 토큰 개수만큼 메모리 할당
	parse->token_count = num_tokens;
	while (i < num_tokens)
	{
		parse->tokens[i] = set_token(tokens_str[i], i); // 각각 토큰 타입, 토큰 인덱스, 토큰 문자열 설정 후 토큰 배열에 넣기
		i++;
	}
}

