/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dequoted_merge_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 22:43:52 by mi                #+#    #+#             */
/*   Updated: 2023/07/17 23:32:47 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_strs_count(t_quote *head)
{
	int		count;
	t_quote	*current;

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
