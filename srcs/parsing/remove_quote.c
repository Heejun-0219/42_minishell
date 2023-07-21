/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 19:27:16 by mi                #+#    #+#             */
/*   Updated: 2023/07/21 22:12:49 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**dequoted_merge(t_quote **head)
{
	char	**result;
	t_quote	*current;
	int		strs_count;
	char	*new_str;

	strs_count = get_strs_count(*head);
	result = (char **)ft_malloc(sizeof(char *) * (strs_count + 1));
	current = *head;
	while (current)
	{
		if (current->index != -1)
		{
			result[current->index] = ft_strdup(current->str);
		}
		else
		{
			new_str = ft_strjoin(result[current->subordinate], current->str);
			free(result[current->subordinate]);
			result[current->subordinate] = new_str;
		}
		current = current->next;
	}
	result[strs_count] = NULL;
	return (result);
}

void	split_quote(t_quote **head)
{
	int		flag;
	t_quote	*current;
	t_quote	*new;

	current = *head;
	while (current)
	{
		flag = check_one_word(current->str);
		if (flag == 0)
		{
			new = new_quote_split_list(head, current);
			*head = new;
			current = *head;
			while (current->next && current->next->index != -1)
				current = current->next;
			rearrange_index(head);
		}
		else if (flag == 1)
		{
			current->subordinate = current->index;
		}
		current = current->next;
	}
}

void	dequote(t_quote **head)
{
	t_quote	*current;
	char	*str;
	char	*new_str;
	int		len;

	current = *head;
	while (current)
	{
		if (current->next && ft_strrchr(current->str, '$') && \
			(current->next->str[0] == '\"' || current->next->str[0] == '\''))
		{
			str = ft_strrchr(current->str, '$');
			*str = '\0';
		}
		if (current->str[0] == '\'' || current->str[0] == '\"')
		{
			str = current->str;
			len = ft_strlen(str);
			new_str = ft_substr(str, 1, len - 2);
			free(str);
			str = NULL;
			current->str = new_str;
		}
		current = current->next;
	}
}

void	modify_index(t_quote **head)
{
	t_quote	*current;
	int		index;
	int		new_subordinate;

	current = *head;
	index = 0;
	while (current)
	{
		if (current->index == current->subordinate)
		{
			new_subordinate = index;
			current->subordinate = index;
			current->index = index++;
		}
		else
		{
			current->subordinate = new_subordinate;
			current->index = -1;
		}
		current = current->next;
	}
}

char	**remove_quote(char **strs)
{
	t_quote	*head;
	char	**result;
	int		i;

	i = 0;
	copy_data_to_node(&head, strs);
	split_quote(&head);
	if (syntax_check(head) == -1)
	{
		destroy_nodes(&head);
		while (strs[i])
			free(strs[i++]);
		free(strs);
		return (NULL);
	}
	dequote(&head);
	modify_index(&head);
	result = dequoted_merge(&head);
	destroy_nodes(&head);
	while (strs[i])
		free(strs[i++]);
	free(strs);
	return (result);
}
