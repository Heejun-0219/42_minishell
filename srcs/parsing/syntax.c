/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:00:59 by mi                #+#    #+#             */
/*   Updated: 2023/07/21 15:20:44 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_check(t_quote *head)
{
	char	*str;

	while (head)
	{
		str = head->str;
		if (str[0] == '\'')
		{
			str++;
			while (*str && *str != '\'')
				str++;
			if (*str != '\'')
				return (-1);
		}
		else if (str[0] == '\"')
		{
			str++;
			while (*str && *str != '\"')
				str++;
			if (*str != '\"')
				return (-1);
		}
		head = head->next;
	}
	return (1);
}

int	print_syntax_error(void)
{
	printf("minishell: syntax error\n");
	g_exit_code = 258;
	return (-1);
}
