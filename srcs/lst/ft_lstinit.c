#include "minishell.h"

t_list	ft_lst_init(void)
{
	t_list	res;

	res.front = NULL;
	res.back = NULL;
	res.cur = NULL;
	return (res);
}
