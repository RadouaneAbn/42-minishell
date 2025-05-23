#include <parser.h>

void	print_tree_(t_tree *tree)
{
	while (tree)
	{
		if (tree->data)
			printf("%d %s\n", tree->data_type, (char *)tree->data);
		else
			printf("%d\n", tree->data_type);
		tree = tree->next;
	}
}

void	print_tree(t_tree *tree)
{
	print_tree_(tree->next);
	if (tree->next->sibling->next)
	{
		print_tree_(tree->next->sibling->next);
		print_tree_(tree->next->sibling->next->sibling);
	}
}

