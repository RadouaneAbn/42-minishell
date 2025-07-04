#include <minishell.h>

int	get_byte_len(int len)
{
	int	size;

	size = len / 8 + ((len - (len / 8 * 8)) != 0);
	return (size);
}

void	print_bit(unsigned char byte)
{
	int				index;
	unsigned char	bit;

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
	while (index < size)
	{
		print_bit(quote_array[index]);
		index++;
	}
}

void	shift_bits(char *quote_array, int size)
{
	int	index;
	int	rest;

	index = get_byte_len(size) - 1;
	if (size % 8 != 0)
	{
		rest = 8 - (size % 8);
		quote_array[index] = quote_array[index] << rest;
	}
}
