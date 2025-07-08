#include <minishell.h>

t_tree	*tree_get_last_sibling(t_tree *tree)
{
		while (tree->sibling)
					tree = tree->sibling;
			return (tree);
}
