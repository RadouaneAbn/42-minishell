#include <minishell.h>

char **	tree_expand_simple_command(t_tree *simple_command)
{
	// size_t	len;
	char *node;
	int	index;
	char	**expand_str;
	char	**quote_array;

	index = 0;
	// len = 0;
	expand_str = malloc(sizeof(char *) * (tree_get_size(simple_command) + 1));
	quote_array = malloc(sizeof(char *) * tree_get_size(simple_command));
	while (simple_command)
	{
		node = simple_command->data;
		expand_str[index] = malloc(sizeof(char) * (expand_str_len(node)) + 1);
		quote_array[index] = ft_calloc(get_byte_len(expand_str_len(node)), sizeof(char));
		expand(node, expand_str[index], quote_array[index]);
		shift_bits(quote_array[index], expand_str_len(node));
		simple_command = simple_command->next;
		index++;
	}
	expand_str[index] = NULL;
	return (filed_splitting(expand_str, quote_array));
	// return (expand_str);
}
