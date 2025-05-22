#include <parser.h>

void	print_tree_(t_tree *tree)
{
	while (tree)
	{
		char *hey = tree->data;
		if (tree->data)
		printf("%d %s\n", tree->data_type, tree->data);
		else
			printf("%d\n", tree->data_type);
		tree = tree->next;
	}
}

void	print_tree(t_tree *tree)
{
	// simple_command => argument_list
	print_tree_(tree);
	print_tree_(tree->next->sibling);
	print_tree_(tree->next->sibling->next->sibling);
	//print_tree_(tree->next);
	////simple_command C=> argument_list  S=> io_redirect
	//print_tree_(tree->next->sibling);
	//print_tree_(tree->next->sibling->next->sibling);
}

