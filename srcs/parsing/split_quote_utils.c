/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 19:30:50 by mi                #+#    #+#             */
/*   Updated: 2023/07/17 22:44:01 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_one_word(char *str)
{
	int	len;

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

void rearrange_index(t_quote **head)
{
	t_quote *current;
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

int quote_split_strs_count(char *str)
{
	int count;
	int len;

	count = 0;
	len = 0;
	while (str[len])
	{
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
		count++;
	}
	return (count);
}

char **make_quote_split_strs(char *str)
{
	int strs_count;
	char **result;
	int i;
	int word_len;

	strs_count = quote_split_strs_count(str);
	result = (char **)malloc(sizeof(char *) * (strs_count + 1));
	i = 0;
	result[strs_count] = NULL;
	while (i < strs_count)
	{
		if (*str == '\'')
		{
			result[i] = ft_substr(str, 0, ft_strchr(str + 1, '\'') - str + 1);
			str = ft_strchr(str + 1, '\'') + 1;
		}
		else if (*str == '\"')
		{
			result[i] = ft_substr(str, 0, ft_strchr(str + 1, '\"') - str + 1);
			str = ft_strchr(str + 1, '\"') + 1;
		}
		else
		{
			word_len = len_one_word(str);
			result[i] = ft_substr(str, 0, word_len);
			str += word_len;
		}
		i++;
	}
	return result;
}
