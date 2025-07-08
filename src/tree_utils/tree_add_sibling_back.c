#include <minishell.h>

void	tree_add_sibling_back(t_tree **head, t_tree *new)
{
	t_tree	*last_sibling;

	if (*head == NULL)
		(*head) = new;
	else
	{
		last_sibling = tree_get_last_sibling(*head);
		last_sibling->sibling = new;
	}
}
