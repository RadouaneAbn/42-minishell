#include <parser.h>

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


//int	main(void)
//{
	//t_tree *head;
	//head = NULL;
	////t_tree *hey = tree_create_new(4, "hey hey");
	//tree_add_back(&head, tree_create_new(3, "number 1"));
	//tree_add_back(&head, tree_create_new(4, "number 2"));
	//tree_add_back(&head, tree_create_new(4, "number 3"));
	//tree_add_sibling_back(&head, tree_create_new(4, "I'm one of siblings"));
	//printf("%s\n", head->sibling->data);
	//printf("%s\n", head->data);
	//printf("%s\n", head->next->data);
	//printf("%s\n", (tree_get_last(head)->data));
	//free(head->sibling);
	//free(head->next->next);
	//free(head->next);
	//free(head);
	//return (0);
//}
