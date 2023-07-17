/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_quote_split_strs_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 23:14:49 by mi                #+#    #+#             */
/*   Updated: 2023/07/18 00:24:33 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_split_strs_count(char *str)
{
	int	count;
	int	len;

	count = 0;
	len = 0;
	while (str[len])
	{
		len += len_one_word(&str[len]);
		count++;
	}
	return (count);
}

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

char	*put_splited_str_spilt_strs(char **result, char *str, int i, char quote)
{
	result[i] = ft_substr(str, 0, ft_strchr(str + 1, quote) - str + 1);
	return (ft_strchr(str + 1, quote) + 1);
}
