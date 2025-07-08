#include <minishell.h>

t_fields_info expand_simple_command(char *str)
{
	char	*expand_str;
	char	*quote_mask;
	char	**fields;
	t_list	*star_mask;
	size_t	expand_len;
	//t_tree	*new_tree;

	expand_len = expand_str_len(str);
	if (expand_len == 0)
		return ((t_fields_info){NULL, NULL});
	star_mask = NULL;
	expand_str = malloc(sizeof(char) * (expand_len) + 1);
	quote_mask = ft_calloc(get_byte_len(expand_len), sizeof(char));
	parameter_expansion(str, expand_str, quote_mask);
	shift_bits(quote_mask, expand_len);
	fields = field_splitting(&expand_str, &quote_mask, &star_mask);
	//if (fields == NULL)
		//return ;
	return ((t_fields_info){fields, star_mask});
}

t_tree *tree_expand_simple_command(t_tree *simple_command)
{
	t_tree				*tree;
	t_fields_info	fields_info;
	t_tree	*new_tree;

	tree = NULL;
	while (simple_command)
	{
		fields_info = expand_simple_command(simple_command->data);
		print_strings(fields_info.fields);
		if (fields_info.fields)
		{
				new_tree = pathname_expansion(fields_info.fields, fields_info.star_mask);
				tree_add_back(&tree, new_tree);
		}
		simple_command = simple_command->next;
	}
	print_tree(tree, 0);
	return (NULL);
}



void redirection_expand(char *filename, bool *ambiguous)
{
	t_tree	*tree;
	t_fields_info	fields_info;

	*ambiguous = false;
	fields_info = expand_simple_command(filename);
	if (strings_len(fields_info.fields) != 1)	
	{
		*ambiguous = true;
		return;// (NULL);
	}
	tree = pathname_expansion(fields_info.fields, fields_info.star_mask);
	if (tree_get_size(tree) != 1)
	{
		*ambiguous = true;
		return;
	}
}
