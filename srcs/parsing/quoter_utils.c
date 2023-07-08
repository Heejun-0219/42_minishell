/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoter_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:18:56 by mi                #+#    #+#             */
/*   Updated: 2023/07/09 06:29:07 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	end_of_quoter_check(char **str, int *merge_str_len, int i, char quoter)
{
	int	merge_count;

	merge_count = 0;
	if (str[i] == NULL)
		return (-1);
	if (ft_count_char(str[i], quoter) >= 2)
		return (0);
	i++;
	while (1)
	{
		if (str[i] == NULL)
			return (-1);
		merge_count++;
		*merge_str_len += strlen(str[i]);
		if (ft_strchr(str[i], quoter) != NULL && str[i] != NULL)
			break ;
		i++;
	}
	return (merge_count);
}

char	*merge_string(char **strs, int start, int merge_len, int merge_count)
{
	char	*merge_str;
	int		i;
	int		total_len;

	i = 0;
	total_len = strlen(strs[start]) + merge_len + merge_count + 1;
	merge_str = (char *)malloc(total_len);
	strcat(merge_str, strs[start]);
	free(strs[start]);
	while (i < merge_count)
	{
		strcat(merge_str, " ");
		strcat(merge_str, strs[start + i + 1]);
		free(strs[start + i + 1]);
		i++;
	}
	return (merge_str);
}

void	del_quoter(char *str, char quoter)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = strlen(str);
	while (i < len)
	{
		if (str[i] == quoter)
		{
			j = i;
			while (j < len - 1)
			{
				str[j] = str[j + 1];
				j++;
			}
			len--;
		}
		i++;
	}
	str[j] = '\0';
}

int	rearange_strs(char **strs, int start, int num_strs, int merge_count)
{
	size_t	size;
	int		i;
	int		src_index;

	i = 0;
	while (i < num_strs - (merge_count + start + 1))
	{
		src_index = start + i + merge_count + 1;
		size = strlen(strs[src_index]) + 1;
		strs[start + i + 1] = malloc(size);
		ft_memmove(strs[start + i + 1], strs[src_index], size);
		free(strs[src_index]);
		i++;
	}
	strs[start + i + 1] = NULL;
	return (start + i + 1);
}

void extra_strs_set_null(char **strs, int new, int old)
{
	int i;

	i = new;
	while (i < old)
	{
		if (strs[i] != NULL && strcmp(strs[i], "") == 0)
			strs[i] = NULL;
		i++;
	}
}
