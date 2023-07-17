/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:18:56 by mi                #+#    #+#             */
/*   Updated: 2023/07/17 23:22:51 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*push_str_to_endpoint(char *str, char endpoint)
{
	while (*str && *str != endpoint)
		str++;
	if (*str == '\0')
		return (NULL);
	return (str + 1);
}
