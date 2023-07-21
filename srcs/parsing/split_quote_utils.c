/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 19:30:50 by mi                #+#    #+#             */
/*   Updated: 2023/07/20 16:34:39 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_one_word_push_to_endpoint(char *str, char c)
{
	str++;
	while (*str && *str != c)
		str++;
	if (*str == c)
		str++;
	else
		return (-1);
	if (*str == '\0')
		return (1);
	return (0);
}

int	check_one_word(char *str)
{
	if (*str == '\'')
		return (check_one_word_push_to_endpoint(str, '\''));
	else if (*str == '\"')
		return (check_one_word_push_to_endpoint(str, '\"'));
	else
	{
		while (*str)
		{
			if (*str == '\'' || *str == '\"')
				return (0);
			str++;
		}
		return (1);
	}
}

void	rearrange_index(t_quote **head)
{
	t_quote	*current;
	int		index;

	current = *head;
	index = 0;
	while (current)
	{
		current->index = index;
		index++;
		current = current->next;
	}
}

t_quote	*new_quote_split_list(t_quote **head, t_quote *current)
{
	char	**splited_str;
	t_quote	*new_list;
	t_quote	*new_start;
	int		i;

	i = 0;
	new_start = NULL;
	splited_str = make_quote_split_strs(current->str);
	new_list = prev_list_copy(head, current->index, &new_start);
	new_list = strs_to_list(splited_str, current, new_list, &new_start);
	new_list = next_list_copy(current->next, new_list);
	destroy_nodes(head);
	while (splited_str[i])
		free(splited_str[i++]);
	free(splited_str);
	return (new_start);
}
