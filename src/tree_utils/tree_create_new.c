#include <minishell.h>

t_tree *tree_create_new(int data_type, void *parameter)
{
	t_tree	*new;

	new = malloc(sizeof(t_tree));
	if (new == NULL)
		return (NULL);
	new->data_type = data_type;
	new->data = parameter;
	new->next = NULL;
	new->sibling = NULL;
	return (new);
}
