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

t_tree	*tree_get_last(t_tree *tree)
{
	while (tree->next)
		tree = tree->next;
	return (tree);
}

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


t_tree	*tree_get_last_sibling(t_tree *tree)
{
	while (tree->sibling)
		tree = tree->sibling;
	return (tree);
}

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
