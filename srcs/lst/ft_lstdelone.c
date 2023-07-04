/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:44:54 by heejunki          #+#    #+#             */
/*   Updated: 2022/11/25 23:38:12 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_del_node(t_node *node)
{
	t_node	*node1;
	t_node	*node2;

	node1 = node->prev;
	node2 = node->next;
	free(node->content);
	free(node);
	node1->next = node2;
	node2->prev = node1;
}

static void	ft_del_front_node(t_list *list, t_node *node)
{
	t_node	*node_temp;

	node_temp = node->next;
	node_temp->prev = NULL;
	free(node->content);
	free(node);
	list->front = node_temp;
	list->cur = node_temp;
}

static void	ft_del_back_node(t_list *list, t_node *node)
{
	t_node	*node_temp;

	node_temp = node->prev;
	node_temp->next = NULL;
	free(node->content);
	free(node);
	list->back = node_temp;
	list->cur = list->front;
}

static void	ft_del_cur_node(t_list *list, t_node *node)
{
	ft_del_node(node);
	list->cur = list->front;
}

int	ft_lstdel_node(t_list *list, t_node *node)
{
	if (list == NULL || node == NULL)
		return (ft_error("argument has been wrong", FAILURE));
	if (node->next == NULL && node->prev == NULL)
	{
		free(node->content);
		free(node);
		*list = ft_lst_init();
		return (SUCCESS);
	}
	if (list->front == node)
		ft_del_front_node(list, node);
	else if (list->back == node)
		ft_del_back_node(list, node);
	else if (list->cur == node)
		ft_del_cur_node(list, node);
	else
		ft_del_node(node);
	return (SUCCESS);
}
