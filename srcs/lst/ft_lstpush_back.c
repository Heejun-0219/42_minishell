#include "minishell.h"

int ft_lstpush_back(t_list *list, void *content)
{
    t_node  *new_node;

    if (list == NULL || content == NULL)
        return (ft_error("ft_list_push_back: list or content is NULL", 1));
    new_node = (t_node *)malloc(sizeof(t_node));
    if (new_node == NULL)
        return (ft_error("ft_list_push_back: malloc failed", 1));
    new_node->content = content;
    new_node->next_node = NULL;
	new_node->prev_node = list->back_node;
	if (new_node->prev_node != NULL)
		new_node->prev_node->next_node = new_node;
	if (list->front_node == NULL)
	{
		list->front_node = new_node;
		list->back_node = new_node;
		list->cur_node = new_node;
		return (SUCCESS);
	}
	list->back_node = new_node;
	return (SUCCESS);
}
