/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 02:50:25 by mi                #+#    #+#             */
/*   Updated: 2023/07/16 02:57:01 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_strs_count(t_del_quote *head)
{
	int count;
	t_del_quote *current;

	count = 0;
	current = head;
	while (current)
	{
		if (current->index == current->subordinate)
			count++;
		current = current->next;
	}
	return (count);
}