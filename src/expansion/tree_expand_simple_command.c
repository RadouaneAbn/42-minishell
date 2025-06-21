#include <minishell.h>

int	hey(int len)
{
	int	size;

	size = len / 4 + ((len - (len / 4 * 4)) != 0);
	return (size);
}

void	tree_expand_simple_command(t_tree *simple_command)
{
	size_t	len;
	char *node;
	int	index;
	char	**whole_string;
	char	**quote_array;

	index = 0;
	len = 0;
	whole_string = malloc(sizeof(char *) * tree_get_size(simple_command));
	quote_array = malloc(sizeof(char *) * tree_get_size(simple_command));
	while (simple_command)
	{
		node = simple_command->data;
		whole_string[index] = malloc(sizeof(char) * (expand_str_len(node)) + 1);
		quote_array[index] = malloc(sizeof(char) * hey(expand_str_len(node)));
		expand(node, whole_string[index]);
		ft_bzero(quote_array[index], hey(expand_str_len(node)));
		simple_command = simple_command->next;
		index++;
	}
}
