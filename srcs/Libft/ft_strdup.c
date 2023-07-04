/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:48:32 by heejunki          #+#    #+#             */
/*   Updated: 2022/11/10 15:43:23 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*newsrc;
	int		src_len;
	int		i;

	src_len = 0;
	i = 0;
	while (src[src_len])
		src_len++;
	newsrc = (char *) malloc (sizeof (char) * (src_len + 1));
	if (!newsrc)
		return (0);
	while (src[i])
	{
		newsrc[i] = src[i];
		i++;
	}
	newsrc[i] = '\0';
	return (newsrc);
}
