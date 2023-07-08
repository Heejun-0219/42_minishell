/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:14:05 by mi                #+#    #+#             */
/*   Updated: 2023/07/09 06:30:31 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int handling_quoter_type(char **strs, int i, int *num_strs)
{
	if (ft_strchr(strs[i], '\'') != NULL)
	{
		*num_strs = single_quoter_process(strs, i, *num_strs);
		del_quoter(strs[i], '\'');
	}
	else if (ft_strchr(strs[i], '\"') != NULL)
	{
		*num_strs = double_quoter_process(strs, i, *num_strs);
		del_quoter(strs[i], '\"');
	}
	if (*num_strs == -1)
		return (-1);
	return (i);	// 다음 인덱스
}

int	single_quoter_process(char **strs, int start, int num_strs)
{
	int	merge_count;
	int	merge_str_len;

	merge_str_len = strlen(strs[start]);
	merge_count = end_of_quoter_check(strs, &merge_str_len, start, '\'');
	if (merge_count == -1)
		return (-1);
	strs[start] = merge_string(strs, start, merge_str_len, merge_count);
	return (rearange_strs(strs, start, num_strs, merge_count));
}

int	double_quoter_process(char **strs, int start, int num_strs)
{
	int	merge_count;
	int	merge_str_len;

	merge_str_len = strlen(strs[start]);
	merge_count = end_of_quoter_check(strs, &merge_str_len, start, '\"');
	if (merge_count == -1)
		return (-1);
	strs[start] = merge_string(strs, start, merge_str_len, merge_count);
	return (rearange_strs(strs, start, num_strs, merge_count)); // 배열의 마지막 인덱스
}

void	merge_quoted_tokens(char **strs, int num_strs)
{
	int	i;

	i = 0;
	while (strs[i] != NULL)
	{
		i = handling_quoter_type(strs, i, &num_strs);
		if (i == -1)
		{
			printf("Error : Quoter is not closed\n");
			exit(1);
		}
		i++;
	}
}
