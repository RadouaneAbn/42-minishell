#include <minishell.h>

void	tree_add_back(t_tree **head, t_tree *new)
{
	t_tree	*last_node;

	if (*head == NULL)
		(*head) = new;
	else
	{
		last_node = tree_get_last(*head);
		last_node->next = new;
	}
}
