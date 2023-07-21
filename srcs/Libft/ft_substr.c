/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 12:53:51 by heejunki          #+#    #+#             */
/*   Updated: 2022/11/19 19:49:14 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*p;
	size_t			index;
	unsigned int	strlen;

	if (!s)
		return (NULL);
	strlen = ft_strlen(s);
	if (len + start > strlen)
		len += strlen - len - start;
	if (start > strlen)
		len = 0;
	p = (char *)malloc((sizeof(char) * (1 + len)));
	if (!p)
		return (NULL);
	p[len] = '\0';
	index = 0;
	while (index < len)
	{
		p[index] = s[start + index];
		index++;
	}
	return (p);
}
