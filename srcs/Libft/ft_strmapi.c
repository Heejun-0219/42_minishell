/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 14:30:03 by heejunki          #+#    #+#             */
/*   Updated: 2022/11/13 14:41:57 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*p;
	int		index;
	int		len;

	len = ft_strlen(s);
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (!p)
		return (0);
	index = 0;
	p[len] = '\0';
	while (index < len)
	{
		p[index] = f(index, s[index]);
		index++;
	}
	return (p);
}
