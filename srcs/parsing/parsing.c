#include "../../includes/minishell.h"

t_token	set_token(t_parse *parse, char *token_str, int index)
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

void tokenize_line(t_parse *parse) // 라인을 쪼개서, 토큰화 시킴
{
	char	**tokens_str;
	size_t	num_tokens;
	size_t	i;

	num_tokens = 0;
	i = 0;
	tokens_str = ft_split(parse->line, " ");			//TODO : 나중에 free 해줘야함
	while (tokens_str[num_tokens] != NULL)
		num_tokens++;							// 토큰 개수 세기
	parse->tokens = ft_realloc(parse->tokens, sizeof(t_token) * (num_tokens));	// 토큰 개수만큼 메모리 할당
	parse->token_count = num_tokens;
	while (i < num_tokens)
	{
		parse->tokens[i] = set_token(parse, tokens_str[i], i);		// 각각 토큰 타입, 토큰 인덱스, 토큰 문자열 설정 후 토큰 배열에 넣기
		i++;
	}
}
