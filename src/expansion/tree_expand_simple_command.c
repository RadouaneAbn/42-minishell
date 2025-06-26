#include <minishell.h>

int	hey(int len)
{
	int	size;

	size = len / 8 + ((len - (len / 8 * 8)) != 0);
	return (size);
}

void print_bit(unsigned char byte)
{
		int	index;
		unsigned char bit;

		index = 0;
		while (index < 8)
		{
			bit = byte >> 7;
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


void	tree_expand_simple_command(t_tree *simple_command)
{
	size_t	len;
	char *node;
	int	index;
	char	**whole_string;
	char	**quote_array;

	index = 0;
	len = 0;
	whole_string = malloc(sizeof(char *) * (tree_get_size(simple_command) + 1));
	quote_array = malloc(sizeof(char *) * tree_get_size(simple_command));
	while (simple_command)
	{
		node = simple_command->data;
		whole_string[index] = malloc(sizeof(char) * (expand_str_len(node)) + 1);
		quote_array[index] = malloc(sizeof(char) * hey(expand_str_len(node)));
		ft_bzero(quote_array[index], hey(expand_str_len(node)));
		expand(node, whole_string[index], quote_array[index]);
		add_bits(quote_array[index], expand_str_len(node));
		//print_bits(quote_array[index], hey(expand_str_len(node)));
		simple_command = simple_command->next;
		index++;
	}
	whole_string[index] = NULL;
	filed_splitting(whole_string, quote_array);
}
