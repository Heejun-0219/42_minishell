/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:28:13 by heejunki          #+#    #+#             */
/*   Updated: 2023/07/06 14:28:22 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error(char *m, int error)
{
	printf("Error\n%s\n", m);
	return (error);
}

int	ft_perror(int error)
{
	perror("Error");
	return (error);
}
