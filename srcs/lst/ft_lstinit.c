/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:36:35 by heejunki          #+#    #+#             */
/*   Updated: 2023/07/06 14:36:35 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	ft_lst_init(void)
{
	t_list	res;

	res.front = NULL;
	res.back = NULL;
	res.cur = NULL;
	return (res);
}
