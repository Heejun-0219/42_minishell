/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_quote_split_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 22:34:08 by mi                #+#    #+#             */
/*   Updated: 2023/07/17 22:55:18 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_quote *prev_list_copy(t_quote **head, int index, t_quote **new)
{
	t_quote *head_cur;
	t_quote *new_list;
	int i;

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

t_quote *strs_to_list(char **strs, t_quote *cur, t_quote *list, t_quote **new)
{
	int i;
	int index;

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

t_quote *next_list_copy(t_quote *head_cur, t_quote *new_list)
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

//? 이전코드
t_quote *new_quote_split_list(t_quote **head, t_quote *current)
{
	char **splited_str;
	t_quote *new_list = NULL;
	t_quote *new_start = NULL;
	t_quote *head_cur;
	int i = 0;

	splited_str = make_quote_split_strs(current->str);
	new_list = prev_list_copy(head, current->index, &new_start);
	new_list = strs_to_list(splited_str, current, new_list, &new_start);
	new_list = next_list_copy(current->next, new_list);
	destroy_nodes(head);
	while (splited_str[i])
		free(splited_str[i++]);
	free(splited_str);
	return new_start;
}