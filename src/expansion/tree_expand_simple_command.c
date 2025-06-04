#include <minishell.h>

void	tree_expand_simple_command(t_tree *simple_command)
{
	char	*str;
	char	*command;
	//size_t	*quote_list;
	size_t	len;
	char *node;

	len = 0;
	t_tree	*tmp = simple_command;
	while (simple_command)
	{
		str = malloc(sizeof(char) * (expand_str_len(node)) + 1);
		node = simple_command->data;
		len += expand_str_len(node);
		printf("%s => %zu\n", node, len);
		simple_command = simple_command->next;
		free(str);
	}
	printf("%zu\n", len);
	command = malloc(sizeof(char) * len);
	expand(tmp->data, command);
	printf("%s\n", command);
}
