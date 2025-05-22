#include <parser.h>

void	print_tree(t_tree *tree)
{
	while (tree)
	{
		printf("%s\n", tree->data);
		tree = tree->next;
	}
}
