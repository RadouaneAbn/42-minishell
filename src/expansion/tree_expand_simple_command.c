#include <minishell.h>

int	hey(int len)
{
	int	size;

	size = len / 8 + ((len - (len / 8 * 8)) != 0);
	return (size);
}

void print_bit(unsigned char byte)
{
		int	index = 0;

		while (index < 8)
		{
			unsigned char bit =  byte >> 7;
			byte = byte << 1;
			printf("%d ", bit);
			index++;
		}
	}
void	print_bits(char *quote_array, int size)
{
	int	index;

	index = 0;
	while(index < size)
	{
		print_bit(quote_array[index]);
		index++;
	}
}

void	add_bits(char *quote_array, int size)
{
	int	index;
	int	rest;

	index = hey(size) - 1;
	if (size % 8 != 0)
	{
		rest = 8 - (size % 8);
		quote_array[index] = quote_array[index] << rest;
	}
}

bool	field_char_quoted(char *quote_mask, int size)
{
	int	index;
	int	index;
	int	bit_index;
	bool	quoted;
	unsigned char is_quote;

	index = 0;
	quoted = false;
	is_quote = false;
	while (index <= size)
	{
		bit_index = index % 8;
		index = index / 8;
		is_quote = (unsigned char)(quote_mask[index] << bit_index) >> 7;
		if (is_quote)
			quoted = !quoted;
		index++;
	}
	return (quoted);
}

int	get_fields_len(char **expand_strs, char **quote_mask)
{
	int	field_len;
	int	str_index;
	int	index;

	field_len = 0;
	str_index = 0;
	while (expand_strs[str_index])
	{
		index = 0;
		while (char_in_set(expand_strs[str_index][index], "\n\t "))
			index++;
		while (expand_strs[str_index][index])
		{
			//printf("%c %d\n", expand_strs[str_index][index], field_char_quoted(quote_mask, index));
			if ((char_in_set(expand_strs[str_index][index + 1], "\t\n ")
							&& !field_char_quoted(quote_mask[str_index], index + 1))
					|| !expand_strs[str_index][index + 1])
					field_len++;
			index++;
		}
		//printf("%d\n", field_len);
		str_index++;
	}
	return (field_len);
}

void	cp_field(char *field, char *expand_str, char *quote_mask, size_t start, size_t end)
{
	size_t	exp_index;

	exp_index = 0;
	while (start < end)
	{
		if (!get_bit(quote_mask, start))
		{
			field[exp_index] = expand_str[start];
			exp_index++;
		}
		index++;
	}
}

size_t	get_field_len(expand_str, quote_mask)
{
	size_t	len;
	size_t	index;

	index = 0;
	len = 0;
	while (char_in_set(expand_str[index], "\t\n "))
		index++;
	while (char_in_set(expand_str[index]))
	{
		if (!get_bit(quote_mask, index))
			len++;
		index++;
	}
	return (len);
}

void	set_field(char *field, char *expand_str, char *quote_mask, size_t start, size_t end)
{
	size_t	len;

	len = get_field_len(expand_str, quote_mask);
	field = malloc(sizeof(char) * (len + 1));
	cp_field(field, expand_str, quote_mask, start, end);
}

void	fill_fields(char **expand_strs, char **fields, char **quote_mask)
{
	int	str_index;
	int	index;
	int	fields_len;
	size_t	start;

	str_index = 0;
	while (expand_strs[index])
	{
		index = 0;
		start = 0;
		while (char_in_set(expand_strs[str_index][index], "\n\t "))
			index++;
		start = index;
		while (expand_strs[str_index][index])
		{
			if ((char_in_set(expand_strs[str_index][index + 1], "\t\n ")
							&& !field_char_quoted(quote_mask[str_index], index + 1))
					|| !expand_strs[str_index][index + 1])
			{
				set_field(expand_strs[str_index], quote_mask[str_index], start, index);
				start = index;
			}
			index++;
		}
		str_index++;
	}
}

void	filed_splitting(char **expand_strs, char **quote_mask)
{
	int	fields_len;
	char	**fields;

	fields_len = get_fields_len(expand_strs, quote_mask);
	fields = malloc(sizeof(char *) * (fields_len + 1));
	fill_fields(expand_strs, fields, quote_mask);
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
		whole_string[index] = malloc(sizeof(char) * (expand_strs_len(node)) + 1);
		quote_array[index] = malloc(sizeof(char) * hey(expand_strs_len(node)));
		ft_bzero(quote_array[index], hey(expand_strs_len(node)));
		expand(node, whole_string[index], quote_array[index]);
		add_bits(quote_array[index], expand_strs_len(node));
		//print_bits(quote_array[index], hey(expand_strs_len(node)));
		simple_command = simple_command->next;
		index++;
	}
		whole_string[index] = NULL;
	filed_splitting(whole_string, quote_array);
}
