/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 19:29:08 by mi                #+#    #+#             */
/*   Updated: 2023/07/17 23:25:07 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_data_to_node(t_quote **head, char **strs)
{
	int		i;
	t_quote	*new;
	t_quote	*current;

	i = 0;
	current = *head;
	while (strs[i] && strs[i][0] != '\0')
	{
		new = new_quote_node(strs[i], i, -1);
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

t_quote	*new_quote_node(char *str, int index, int subordinate)
{
	t_quote	*new;

	new = (t_quote *)malloc(sizeof(t_quote));
	new->str = strdup(str);
	new->index = index;
	new->subordinate = subordinate;
	new->next = NULL;
	return (new);
}

t_quote	*copy_node(t_quote *node)
{
	t_quote	*new;

	new = (t_quote *)malloc(sizeof(t_quote));
	new->str = strdup(node->str);
	new->index = node->index;
	new->subordinate = node->subordinate;
	new->next = NULL;
	return (new);
}
