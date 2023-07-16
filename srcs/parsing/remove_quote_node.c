/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 02:44:24 by mi                #+#    #+#             */
/*   Updated: 2023/07/16 17:27:51 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_del_quote *new_del_quote_node(char *str, int index, int subordinate)
{
	t_del_quote *new;

	new = (t_del_quote *)malloc(sizeof(t_del_quote));
	new->str = strdup(str);
	new->index = index;
	new->subordinate = subordinate;
	new->next = NULL;
	return (new);
}

void copy_data_to_node(t_del_quote **head, char **strs)
{
	int i;
	t_del_quote *new;
	t_del_quote *current;

	i = 0;
	current = *head;
	while (strs[i])
	{
		new = new_del_quote_node(strs[i], i, -1);
		if (i == 0)
		{
			*head = new;
			current = new;
		}
		else
		{
			current->next = new;
			current = new;
		}
		i++;
	}
}

int get_node_count(t_del_quote *head)
{
	int count;
	t_del_quote *current;

	count = 0;
	current = head;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

t_del_quote *get_tail(t_del_quote *head)
{
	t_del_quote *current;

	current = head;
	while (current->next)
		current = current->next;
	return (current);
}

t_del_quote *get_node_by_index(t_del_quote *head, int index)
{
	t_del_quote *current;

	current = head;
	while (current)
	{
		if (current->index == index)
			return (current);
		current = current->next;
	}
	return (NULL);
}