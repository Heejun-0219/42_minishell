/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 02:37:50 by mi                #+#    #+#             */
/*   Updated: 2023/07/16 17:30:52 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_one_word_push_to_endpoint(char *str, char c)
{
	str++;
	while (*str && *str != c)
		str++;
	if (*str == c)
		str++;
	else
		return (-1);
	if (*str == '\0')
		return 1;
	return (0);
}

int check_one_word(char *str)
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

int len_one_word(char *str)
{
	int len;

	len = 0;
	if (str[len] == '\'')
	{
		len++;
		while (str[len] && str[len] != '\'')
			len++;
		if (str[len] == '\'')
			len++;
	}
	else if (str[len] == '\"')
	{
		len++;
		while (str[len] && str[len] != '\"')
			len++;
		if (str[len] == '\"')
			len++;
	}
	else
	{
		while (str[len] && (str[len] != '\'' && str[len] != '\"'))
			len++;
	}
	return (len);
}

t_del_quote *new_splited_word(char *str, int parent_index, int subordinate)
{
	char *word;
	char *remainder;
	int word_len;
	t_del_quote *new;

	word_len = len_one_word(str);
	word = ft_substr(str, 0, word_len);
	new = new_del_quote_node(word, parent_index, subordinate);
	if (strlen(str) - word_len > 0)
		remainder = ft_substr(str, word_len, strlen(str) - word_len);
	else
		remainder = NULL;
	free(str);
	str = NULL;
	if (remainder)
		new->next = new_splited_word(remainder, parent_index + 1, subordinate);
	else
		new->next = NULL;
	return (new);
}

void rearrange_index(t_del_quote **head)
{
	t_del_quote *current;
	int index;

	current = *head;
	index = 0;
	while (current)
	{
		current->index = index;
		index++;
		current = current->next;
	}
}

t_del_quote *new_quote_split_list(t_del_quote **head, t_del_quote *current)
{
	char **splited_str;
	t_del_quote *new_list = NULL;
	t_del_quote *new_start = NULL;
	t_del_quote *head_cur;
	int i = 0;

	splited_str = make_quote_split_strs(current->str);
	head_cur = *head;

	while (i < current->index)
	{
		if (i == 0)
		{
			new_list = copy_node(head_cur);
			new_start = new_list;
		}
		else
		{
			new_list->next = copy_node(head_cur);
			new_list = new_list->next;
		}
		head_cur = head_cur->next;
		i++;
	}

	i = 0;
	while (splited_str[i])
	{
		if (new_list == NULL)
		{
			new_list = new_del_quote_node(splited_str[i], current->index, current->index);
			new_start = new_list;
		}
		else
		{
			new_list->next = new_del_quote_node(splited_str[i], current->index + i, current->index);
			new_list = new_list->next;
		}
		i++;
	}

	head_cur = current->next;
	while (head_cur)
	{
		new_list->next = copy_node(head_cur);
		new_list = new_list->next;
		new_list->index = -1;
		head_cur = head_cur->next;
	}

	destroy_nodes(head);

	// free splited_str
	for (i = 0; splited_str[i]; i++)
	{
		free(splited_str[i]);
	}
	free(splited_str);

	return new_start;
}