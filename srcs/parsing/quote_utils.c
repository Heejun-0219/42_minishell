/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:18:56 by mi                #+#    #+#             */
/*   Updated: 2023/07/20 23:29:13 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*process_quote(char *str, char c)
{
	while (*str && *str != c)
	{
		if (*str == '\'')
		{
			str++;
			while (*str && *str != '\'')
				str++;
			if (*str && *str == '\'')
				str++;
		}
		else if (*str == '\"')
		{
			str++;
			while (*str && *str != '\"')
				str++;
			if (*str && *str == '\"')
				str++;
		}
		else
			str++;
	}
	return (str);
}

char	*push_str_to_endpoint(char *str, char endpoint)
{
	while (*str && *str != endpoint)
		str++;
	if (*str == '\0')
		return (NULL);
	return (str + 1);
}
