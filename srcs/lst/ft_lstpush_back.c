/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:36:18 by heejunki          #+#    #+#             */
/*   Updated: 2023/07/06 14:36:24 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstpush_back(t_list *list, void *content)
{
	t_node	*new_node;

	if (list == NULL || content == NULL)
		return (ft_error("ft_list_push_back: list or content is NULL", 1));
	new_node = (t_node *)malloc(sizeof(t_node));
	if (new_node == NULL)
		return (ft_error("ft_list_push_back: malloc failed", 1));
	new_node->content = content;
	new_node->next = NULL;
	new_node->prev = list->back;
	if (new_node->prev != NULL)
		new_node->prev->next = new_node;
	if (list->front == NULL)
	{
		list->front = new_node;
		list->back = new_node;
		list->cur = new_node;
		return (SUCCESS);
	}
	list->back = new_node;
	return (SUCCESS);
}
