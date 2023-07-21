/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:59:05 by heejunki          #+#    #+#             */
/*   Updated: 2022/11/10 15:47:02 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *p, int val, size_t len)
{
	size_t			i;
	unsigned char	*tmp;

	i = 0;
	tmp = (unsigned char *)p;
	while (i < len)
	{
		tmp[i++] = (unsigned char)val;
	}
	return (tmp);
}
