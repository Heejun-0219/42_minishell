/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:50:23 by heejunki          #+#    #+#             */
/*   Updated: 2023/07/06 14:54:39 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exe_pwd(void)
{
	char	pwd[256];

	if (getcwd(pwd, 256))
		printf("%s\n", pwd);
	else
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
