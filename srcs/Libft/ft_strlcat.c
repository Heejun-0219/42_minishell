/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:46:49 by heejunki          #+#    #+#             */
/*   Updated: 2022/11/10 15:43:18 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	k;
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	i = dst_len;
	k = 0;
	while (src[k] != '\0' && (dst_len + k + 1) < size)
	{
		dest[i] = src[k];
		k++;
		i++;
	}
	dest[i] = '\0';
	if (dst_len < size)
		return (dst_len + src_len);
	else
		return (size + src_len);
}
