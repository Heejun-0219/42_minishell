/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 22:28:15 by mi                #+#    #+#             */
/*   Updated: 2023/07/06 14:56:20 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	new_ptr = ft_malloc(size);
	ft_memcpy(new_ptr, ptr, size);
	free(ptr);
	return (new_ptr);
}
