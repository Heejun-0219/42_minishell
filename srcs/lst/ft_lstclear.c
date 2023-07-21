/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:52:36 by heejunki          #+#    #+#             */
/*   Updated: 2022/11/25 23:38:29 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstclear(t_list *lst)
{
	lst->cur = lst->front;
	while (lst->cur)
		ft_lstdel_node(lst, lst->cur);
}
