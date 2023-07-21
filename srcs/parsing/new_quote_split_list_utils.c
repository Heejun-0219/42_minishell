/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_quote_split_list_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 22:34:08 by mi                #+#    #+#             */
/*   Updated: 2023/07/21 01:21:22 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_quote	*prev_list_copy(t_quote **head, int index, t_quote **new)
{
	t_quote	*head_cur;
	t_quote	*new_list;
	int		i;

	new_list = NULL;
	head_cur = *head;
	i = 0;
	while (i < index)
	{
		if (i == 0)
		{
			new_list = copy_node(head_cur);
			*new = new_list;
		}
		else
		{
			new_list->next = copy_node(head_cur);
			new_list = new_list->next;
		}
		head_cur = head_cur->next;
		i++;
	}
	return (new_list);
}

t_quote	*strs_to_list(char **strs, t_quote *cur, t_quote *list, t_quote **new)
{
	int	i;
	int	index;

	i = 0;
	index = cur->index;
	while (strs[i])
	{
		if (list == NULL)
		{
			list = new_quote_node(strs[i], index + i, index);
			*new = list;
		}
		else
		{
			list->next = new_quote_node(strs[i], index + i, index);
			list = list->next;
		}
		i++;
	}
	return (list);
}

t_quote	*next_list_copy(t_quote *head_cur, t_quote *new_list)
{
	while (head_cur)
	{
		new_list->next = copy_node(head_cur);
		new_list = new_list->next;
		new_list->index = -1;
		head_cur = head_cur->next;
	}
	return (new_list);
}

char	**make_quote_split_strs(char *str)
{
	int		strs_count;
	char	**result;
	int		i;
	int		word_len;

	strs_count = quote_split_strs_count(str);
	result = (char **)ft_malloc(sizeof(char *) * (strs_count + 1));
	i = 0;
	result[strs_count] = NULL;
	while (i < strs_count)
	{
		if (*str == '\'')
			str = put_splited_str_spilt_strs(result, str, i, '\'');
		else if (*str == '\"')
			str = put_splited_str_spilt_strs(result, str, i, '\"');
		else
		{
			word_len = len_one_word(str);
			result[i] = ft_substr(str, 0, word_len);
			str += word_len;
		}
		i++;
	}
	return (result);
}
