/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:57:46 by heejunki          #+#    #+#             */
/*   Updated: 2022/11/10 15:43:53 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	int		val;

	i = 0;
	while (i < n)
	{
		val = ((unsigned char *)s1)[i] - ((unsigned char *)s2)[i];
		if (val != 0)
			return (val);
		i++;
	}
	return (0);
}
