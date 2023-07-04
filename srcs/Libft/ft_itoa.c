/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 14:05:10 by heejunki          #+#    #+#             */
/*   Updated: 2022/11/19 16:52:42 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	integer_len(int ln)
{
	int	len;

	len = 0;
	if (!ln)
		return (1);
	if (ln < 0)
	{
		len++;
		ln *= -1;
	}
	while (ln)
	{
		ln /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*p;
	int		len;
	long	ln;

	ln = (long)n;
	len = integer_len(ln);
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (!p)
		return (0);
	p[len--] = '\0';
	if (!ln)
		p[0] = '0';
	else if (ln < 0)
	{
		ln *= -1;
		p[0] = '-';
	}
	while (ln)
	{
		p[len--] = ln % 10 + '0';
		ln /= 10;
	}
	return (p);
}
