#include "minishell.h"

t_list	ft_lst_init(void)
{
	t_list	res;

	res.front_node = NULL;
	res.back_node = NULL;
	res.cur_node = NULL;
	return (res);
}
