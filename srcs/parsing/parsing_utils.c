/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:16:42 by mi                #+#    #+#             */
/*   Updated: 2023/07/21 20:57:19 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_strs(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i] != NULL)
		i++;
	return (i);
}

size_t	count(char **strs, size_t i)
{
	size_t	count;
	size_t	index;

	count = 0;
	index = 0;
	while (strs[i] && index < i)
	{
		if (strs[index] != NULL)
			count++;
		index++;
	}
	return (count);
}
