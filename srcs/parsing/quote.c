/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:14:05 by mi                #+#    #+#             */
/*   Updated: 2023/07/21 01:25:39 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_quote_set_flag(char *str, int *flag)
{
	if (*str == '\'')
		str = push_str_to_endpoint(++str, '\'');
	else if (*str == '\"')
		str = push_str_to_endpoint(++str, '\"');
	else
	{
		*flag = 1;
		return (str);
	}
	*flag = 0;
	return (str);
}

int	get_count_respect_quote(char *str, char c)
{
	int	count;
	int	flag;

	count = 0;
	while (*str)
	{
		if (*str != c)
		{
			count++;
			while (*str && *str != c)
			{
				flag = 1;
				str = check_quote_set_flag(str, &flag);
				if (str == NULL)
					return (-1);
				if (flag)
					str = process_quote(str, c);
			}	
		}
		else
			str++;
	}
	return (count);
}

int	len_respect_quote(char *str, char c)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != c)
	{
		if (str[len] == '\'')
		{
			len++;
			while (str[len] && str[len] != '\'')
				len++;
			if (str[len] == '\0')
				return (len);
		}
		else if (str[len] == '\"')
		{
			len++;
			while (str[len] && str[len] != '\"')
				len++;
			if (str[len] == '\0')
				return (len);
		}
		len++;
	}
	return (len);
}

char	**alloc_split_dismiss_quote(char **result, char *str, char c, int count)
{
	int	str_index;
	int	result_index;
	int	len;

	result[count] = NULL;
	str_index = 0;
	result_index = 0;
	while (result_index < count && str[str_index])
	{
		len = len_respect_quote(str + str_index, c);
		result[result_index] = ft_strndup(str + str_index, len);
		str_index += len;
		result_index++;
		while (str[str_index] && str[str_index] == c)
			str_index++;
	}
	return (result);
}

char	**split_respect_quote(char *str, char c)
{
	char	**result;
	int		count;

	count = get_count_respect_quote(str, c);
	if (count == -1)
		return (NULL);
	result = (char **)ft_malloc(sizeof(char *) * (count + 1));
	if (result == NULL)
		return (NULL);
	result = alloc_split_dismiss_quote(result, str, c, count);
	return (result);
}
