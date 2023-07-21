/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:45:19 by heejunki          #+#    #+#             */
/*   Updated: 2022/11/17 15:20:15 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!n)
		return (0);
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] == s2[i])
			i++;
		else
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	if (n != 0 && i == n)
		i--;
	if (s1[i] == s2[i])
		return (0);
	else
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
