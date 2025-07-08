#include <minishell.h>

t_tree	*tree_get_last(t_tree *tree)
{
		while (tree->next)
					tree = tree->next;
			return (tree);
}
