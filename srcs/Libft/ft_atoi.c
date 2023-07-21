/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:47:54 by heejunki          #+#    #+#             */
/*   Updated: 2023/07/21 22:02:16 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_max_or_min(long num, const char c, int minus)
{
	if (num > LONG_MAX / 10 || (num == LONG_MAX / 10 && c - '0' > 7))
	{
		if (minus == 1)
			return (-1);
		return (0);
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	long	num;
	int		minus;

	num = 0;
	minus = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*(str) == '-' || *(str) == '+')
		if (*(str++) == '-')
			minus *= -1;
	while (*str >= '0' && *str <= '9')
	{
		if (check_max_or_min(num, *str, minus) != 1)
			return (255);
		num = num * 10 + (*str++ - '0');
	}
	return (num * minus);
}
