/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 19:27:16 by mi                #+#    #+#             */
/*   Updated: 2023/07/16 19:50:26 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **dequoted_merge(t_del_quote **head)
{
	char **result;
	t_del_quote *current;
	int strs_count;
	char *new_str;

	strs_count = get_strs_count(*head);
	result = (char **)malloc(sizeof(char *) * (strs_count + 1));
	current = *head;
	while (current)
	{
		if (current->index != -1)
		{
			result[current->index] = strdup(current->str);
		}
		else
		{
			new_str = ft_strjoin(result[current->subordinate], current->str);
			free(result[current->subordinate]);
			result[current->subordinate] = new_str;
		}
		current = current->next;
	}
	result[strs_count] = NULL;
	return (result);
}

void split_quote(t_del_quote **head)
{
	int flag;
	t_del_quote *current;
	t_del_quote *new;

	current = *head;
	while (current)
	{
		flag = check_one_word(current->str);
		if (flag == 0) // 한 단어가 아닌 경우
		{
			new = new_quote_split_list(head, current);
			*head = new;
			current = *head;
			while (current->next && current->next->index != -1)
				current = current->next;
			rearrange_index(head);
		}
		else if (flag == 1) // 한 단어인 경우
		{
			current->subordinate = current->index;
		}
		current = current->next; // Update current node to the next node saved before
	}
}

void dequote(t_del_quote **head)
{
	t_del_quote *current;
	char *str;
	char *new_str;
	int len;

	current = *head;
	while (current)
	{
		if (current->str[0] == '\'' || current->str[0] == '\"')
		{
			str = current->str;
			len = strlen(str);
			new_str = ft_substr(str, 1, len - 2);
			free(str);
			str = NULL;
			current->str = new_str;
		}
		current = current->next;
	}
}

void modify_index(t_del_quote **head)
{
	t_del_quote *current;
	int index;
	int new_subordinate;

	current = *head;
	index = 0;
	while (current)
	{
		if (current->index == current->subordinate)
		{
			new_subordinate = index;
			current->subordinate = index;
			current->index = index++;
		}
		else
		{
			current->subordinate = new_subordinate;
			current->index = -1;
		}
		current = current->next;
	}
}

char **remove_quote(char **strs)
{
	t_del_quote *head;
	char **result;
	int i;

	i = 0;
	copy_data_to_node(&head, strs);
	split_quote(&head);
	dequote(&head);
	modify_index(&head);
	result = dequoted_merge(&head);
	destroy_nodes(&head);
	while (strs[i])
		free(strs[i++]);
	free(strs);
	return (result);
}