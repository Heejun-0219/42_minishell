/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 13:37:17 by heejunki          #+#    #+#             */
/*   Updated: 2022/11/25 23:35:49 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_strlen(char *str, char c, int str_in)
{
	int	len;

	len = 0;
	while (str[str_in] != '\0')
	{
		if (str[str_in] == c)
			return (len);
		len++;
		str_in++;
	}
	return (len);
}

char	*ft_strndup(char *str, size_t str_len)
{
	char	*newsrc;
	size_t	i;

	i = 0;
	newsrc = (char *) malloc (sizeof (char) * (str_len + 1));
	if (!newsrc)
		return (0);
	while (i < str_len)
	{
		newsrc[i] = str[i];
		i++;
	}
	newsrc[i] = '\0';
	return (newsrc);
}

int	get_count(char const *s, char c)
{
	int	count;
	int	len;
	int	flag;

	count = 0;
	flag = 0;
	len = ft_strlen(s);
	while (len--)
	{
		if (s[len] == c)
			flag = 0;
		else if (s[len] != c && !flag)
		{
			flag = 1;
			count++;
		}
	}
	return (count);
}

char	**null_free(char **res)
{
	size_t	j;

	j = 0;
	while (res[j])
	{
		free(res[j]);
		j++;
	}
	free(res);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		str_in;
	int		res_in;
	int		flag;
	int		count;

	count = get_count((char *)s, c);
	result = (char **) malloc (sizeof(char *) * (count + 1));
	if (!result)
		return (0);
	result[count] = 0;
	str_in = 0;
	res_in = 0;
	while (res_in < count && s[str_in])
	{
		while (s[str_in] == c)
			str_in++;
		flag = str_in;
		while (s[str_in] != c && s[str_in])
			str_in++;
		result[res_in] = ft_strndup((char *)s + flag, str_in - flag);
		if (result[res_in++] == 0)
			return (null_free(result));
	}
	return (result);
}
