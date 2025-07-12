#include <minishell.h>

void	free_tree(t_tree *tree)
{
	t_tree	*tmp;

	tmp = tree;
	while (tree)
	{
		free(tree->data);
		free_tree(tree->next);
		tmp = tree;
		tree = tree->sibling;
		free(tmp);
	}
}
