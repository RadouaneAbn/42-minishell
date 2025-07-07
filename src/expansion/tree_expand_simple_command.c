#include <minishell.h>

void expand_simple_command(char *str, t_tree **tree)
{
	char	*expand_str;
	char	*quote_mask;
	char	**fields;
	t_list	*star_mask;
	size_t	expand_len;
	t_tree	*new_tree;

	expand_len = expand_str_len(str);
	star_mask = NULL;
	expand_str = malloc(sizeof(char) * (expand_len) + 1);
	quote_mask = ft_calloc(get_byte_len(expand_len), sizeof(char));
	expand(str, expand_str, quote_mask);
	shift_bits(quote_mask, expand_len);
	fields = field_splitting(&expand_str, &quote_mask, &star_mask);
	new_tree = wild_card_expansion(fields, star_mask);
	tree_add_back(tree, new_tree);
}

t_tree *tree_expand_simple_command(t_tree *simple_command)
{
	t_tree	*tree;

	tree = NULL;
	while (simple_command)
	{
		expand_simple_command(simple_command->data, &tree);
		simple_command = simple_command->next;
	}
	print_tree(tree, 0);
	return (NULL);
}
