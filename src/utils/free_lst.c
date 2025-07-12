#include <minishell.h>

void	free_list(t_list **list)
{
	t_list	*ptr;

	if (list == NULL)
		return ;
	while ((*list) != NULL)
	{
		gc_global_free((*list)->content);
		ptr = (*list)->next;
		gc_global_free((*list));
		*list = ptr;
	}
}

