#include <minishell.h>

void	fill_fields(char *expand_str, char **fields, char *quote_mask, t_list **star_mask_list)
{
	size_t index;
	size_t	start;
	size_t	len;
	size_t	fields_len;

	index = 0;
	fields_len = 0;
	while (expand_str[index])
	{
		if (expand_str[index] && !(is_space(expand_str[index])
					&& !quoted_char(quote_mask, index)))
		{
			start = index;
			len = get_field_len(expand_str, quote_mask, &index);
			fields[fields_len] = malloc(sizeof(char) * (len + 1));
			set_field_info((t_expansion){fields[fields_len], expand_str, quote_mask, star_mask_list},
					(t_range){start, len});
			fields_len++;
		}
		else
			index++;
	}
}

char	**get_fields(char **expand_strs, char **quote_mask, t_list **star_mask_list)
{
	size_t	fields_len;
	char	**fields;

	fields_len = get_fields_len(*expand_strs, *quote_mask);
	if (fields_len == 0)
		return (NULL);
	fields = malloc(sizeof(char *) * (fields_len + 1));
	fill_fields(*expand_strs, fields, *quote_mask, star_mask_list);
	fields[fields_len] = NULL;
	return (fields);
}

t_fields_info expand_simple_command(char *str)
{
	char	*expand_str;
	char	*quote_mask;
	char	**fields;
	t_list	*star_mask;
	size_t	expand_len;

	expand_len = expand_str_len(str);
	if (expand_len == 0)
		return ((t_fields_info){NULL, NULL});
	star_mask = NULL;
	expand_str = ft_calloc(sizeof(char), (expand_len) + 1);
	quote_mask = ft_calloc(get_byte_len(expand_len), sizeof(char));
	parameter_expansion(str, expand_str, quote_mask);
	fields = get_fields(&expand_str, &quote_mask, &star_mask);
	gc_global_free(quote_mask);
	gc_global_free(expand_str);
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
	free_strings(fields_info.fields);
	free_list(&fields_info.star_mask);
	return (NULL);
}

void expand_redirection(char *filename, bool *ambiguous)
{
	t_tree	*tree;
	t_fields_info	fields_info;

	*ambiguous = false;
	fields_info = expand_simple_command(filename);
	if (get_strings_len(fields_info.fields) != 1)	
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
