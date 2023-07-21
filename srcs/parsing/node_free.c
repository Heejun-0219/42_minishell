/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 19:36:04 by mi                #+#    #+#             */
/*   Updated: 2023/07/21 21:52:57 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_nodes(t_quote **head)
{
	t_quote	*current;
	t_quote	*next;

	current = *head;
	while (current)
	{
		next = current->next;
		free_node(current);
		current = next;
	}
}

void	free_node(t_quote *node)
{
	if ((node->str) != NULL)
		free(node->str);
	free(node);
}
