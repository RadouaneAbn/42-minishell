#include <minishell.h>

int	tree_get_size(t_tree *list)
{
	int	len;

	if (list == NULL)
		return (0);
	len = 0;
	while (list != NULL)
	{
		list = list->next;
		len++;
	}
	return (len);
}
