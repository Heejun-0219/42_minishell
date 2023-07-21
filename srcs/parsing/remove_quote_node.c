/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 19:29:08 by mi                #+#    #+#             */
/*   Updated: 2023/07/21 22:14:33 by heejunki         ###   ########.fr       */
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
	while (strs[i] && strs[i] != NULL)
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

	new = (t_quote *)ft_malloc(sizeof(t_quote));
	new->str = ft_strdup(str);
	new->index = index;
	new->subordinate = subordinate;
	new->next = NULL;
	return (new);
}

t_quote	*copy_node(t_quote *node)
{
	t_quote	*new;

	new = (t_quote *)ft_malloc(sizeof(t_quote));
	new->str = ft_strdup(node->str);
	new->index = node->index;
	new->subordinate = node->subordinate;
	new->next = NULL;
	return (new);
}
