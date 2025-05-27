#include <minishell.h>

void	print_tree_(t_tree *tree)
{
	char *data_type[] = {
		"FILE IN",
		"FILE OUT",
		"NONE",
		"CMD ARG"
	};
	while (tree)
	{
		if (tree->data)
			printf("%s %s\n", data_type[tree->data_type], (char *)tree->data);
		else
			printf("%s\n", data_type[tree->data_type]);
		tree = tree->next;
	}
}

void	print_tree(t_tree *tree, int n)
{
	int	i = 0;
	char *data_type[] = {
		"FILE IN",
		"FILE OUT",
		"NONE",
		"CMD ARG",
		"ARGUMENT LIST",
		"SIMPLE COMMAND",
		"IO REDIRECT LIST",
		"SUBSHELL",
		"COMMAND",
		"PIPELINE"
	};
	while (tree)
	{
		i = 0;
		while (i < n)
		{
			i++;
			printf("\t");
		}
		printf("└──%s "BLUE"%s"RESET"\n", data_type[tree->data_type], (char *)tree->data);
		print_tree(tree->next, n + 1);
		tree = tree->sibling;
	}
}

