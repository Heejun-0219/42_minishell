/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoter_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 02:24:10 by mi                #+#    #+#             */
/*   Updated: 2023/07/06 04:00:10 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 문자열을 병합하고 메모리를 해제
void merge_and_free_tokens(char **dest, char *src)
{
	strcat(*dest, " ");
	strcat(*dest, src);
	if (src != NULL)
		free(src);
}

// 문자열이 따옴표(", ')로 끝나는지 검사
int ends_with_quote(char *token)
{
	int result;
	
	result = 0;
	if (token != NULL && token[strlen(token) - 1] == '\"')
		result = 1;
	if (token != NULL && token[strlen(token) - 1] == '\'')
		result = 1;
	return (result);
}

// 문자열 배열의 크기를 반환
size_t get_array_size(char **array)
{
	size_t count = 0;
	while (array[count] != NULL)
		count++;
	return count;
}

// 토큰이 따옴표로 끝나는 경우, 해당 따옴표 내부에 있는지 확인
// int is_end_of_quote_scope(char *token, int inside_double, int inside_single)
// {
// 	if (!ends_with_quote(token))
// 		return 0;

// 	if (token[strlen(token) - 1] == '\"' && inside_double)
// 		return 1;

// 	if (token[strlen(token) - 1] == '\'' && inside_single)
// 		return 1;

// 	return 0;
// }
int is_end_of_quote_scope(char *token, int *quoter_type)
{
	if (!ends_with_quote(token))
		return 0;

	if (token[strlen(token) - 1] == '\"' && quoter_type[1])
		return 1;

	if (token[strlen(token) - 1] == '\'' && quoter_type[1])
		return 1;

	return 0;
}
