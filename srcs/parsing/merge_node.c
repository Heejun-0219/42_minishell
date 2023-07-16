/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 02:46:29 by mi                #+#    #+#             */
/*   Updated: 2023/07/16 03:06:35 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void head_merge(t_del_quote **head, t_del_quote **new)
{
	t_del_quote *next;
	t_del_quote *new_tail;

	next = (*head)->next;
	free_node(*head);
	*head = *new;
	new_tail = get_tail(*new);
	new_tail->next = next;
}

void mid_merge(t_del_quote **head, t_del_quote **new)
{
	t_del_quote *prev;
	t_del_quote *next;
	t_del_quote *new_tail;
	t_del_quote *origin;

	origin = get_node_by_index(*head, (*new)->index);
	prev = get_node_by_index(*head, (*new)->index - 1);
	next = get_node_by_index(*head, (*new)->index + 1);
	new_tail = get_tail(*new);
	prev->next = *new;
	new_tail->next = next;
	free_node(origin);
}

void tail_merge(t_del_quote **head, t_del_quote **new)
{
	t_del_quote *prev;
	t_del_quote *origin;

	origin = get_node_by_index(*head, (*new)->index);
	prev = get_node_by_index(*head, (*new)->index - 1);
	prev->next = *new;
	free_node(origin);
}

t_del_quote **merge_node(t_del_quote **head, t_del_quote **new)
{
	t_del_quote *new_current;

	new_current = *new;
	if (new_current->index == 0)
		head_merge(head, new);
	else if (get_node_count(*head) - 1 == (*new)->index)
		tail_merge(head, new);
	else
		mid_merge(head, new);
	return (head);
}