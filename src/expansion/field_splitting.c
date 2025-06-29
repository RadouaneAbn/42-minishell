#include <minishell.h>

bool	quoted_char(char *quote_mask, int size)
{
	int	index;
	char	tmp_char;
	bool	quoted;
	bool is_quote;

	index = 0;
	quoted = false;
	is_quote = false;
	while (index <= size)
	{
		if ((index % 8) == 0)
			tmp_char = quote_mask[index / 8];
		is_quote = tmp_char >> 7;
		if (is_quote)
			quoted = !quoted;
		tmp_char = tmp_char << 1;
		index++;
	}
	return (quoted | is_quote);
}

int	get_fields_len(char **expand_strs, char **quote_mask)
{
	int	field_len;
	int	str_index;
	int	index;
	bool current_ch_quoted;
	bool next_ch_quoted;

	field_len = 0;
	str_index = 0;
	while (expand_strs[str_index])
	{
		index = 0;
		while (expand_strs[str_index][index])
		{
			current_ch_quoted = quoted_char(quote_mask[str_index], index);
			next_ch_quoted = quoted_char(quote_mask[str_index], index + 1);
			if ((current_ch_quoted || (!current_ch_quoted && !char_in_set(expand_strs[str_index][index], "\t\n ")))
					&& ((char_in_set(expand_strs[str_index][index + 1], "\t\n ") && !next_ch_quoted) || !expand_strs[str_index][index + 1]))
				field_len++;
			index++;
		}
		str_index++;
	}
	return (field_len);
}

unsigned char get_bit(char *quote_mask, size_t size)
{
	unsigned char bit;
	size_t	char_index;
	size_t	bit_index;

	char_index = size / 8;
	bit_index = size % 8;
	bit = (unsigned char)(quote_mask[char_index] << bit_index) >> 7;
	return (bit);
}

void	cp_field(char *field, char *expand_str, char *quote_mask, size_t start, size_t end)
{
	size_t	index;

	index = 0;
	while (start < end)
	{
		if (!get_bit(quote_mask, start))
		{
			field[index] = expand_str[start];
			index++;
		}
		start++;
	}
}

size_t	get_field_len(char *expand_str, char *quote_mask)
{
	size_t	len;
	size_t	index;

	index = 0;
	len = 0;
	while (char_in_set(expand_str[index], "\t\n "))
		index++;
	while (expand_str[index] && !(char_in_set(expand_str[index], "\t\n ")
			&& !quoted_char(quote_mask, index)))
	{
		if (!get_bit(quote_mask, index))
			len++;
		index++;
	}
	return (len);
}

void	set_field(char **field, char *expand_str, char *quote_mask, size_t start, size_t end)
{
	size_t	len;

	len = get_field_len(expand_str, quote_mask);
	*field = malloc(sizeof(char) * (len + 1));
	cp_field(*field, expand_str, quote_mask, start, end);
}

void	fill_fields(char **expand_strs, char **fields, char **quote_mask)
{
	int	str_index;
	size_t index;
	int	field_index;
	size_t	start;

	str_index = 0;
	field_index = 0;
	while (expand_strs[str_index])
	{
		index = 0;
		start = 0;
		while (expand_strs[str_index][index])
		{
			if (expand_strs[str_index][index] && ((char_in_set(expand_strs[str_index][index + 1], "\t\n ")
						&& !quoted_char(quote_mask[str_index], index + 1))
					|| !expand_strs[str_index][index + 1]))
			{
				set_field(fields + field_index, expand_strs[str_index], quote_mask[str_index], start, index + 1);
				field_index++;
			}
			index++;
			while (char_in_set(expand_strs[str_index][index], "\n\t ") && !quoted_char(quote_mask[str_index], index))
			{
				index++;
				start = index;
			}
		}
		str_index++;
	}
}

void	filed_splitting(char **expand_strs, char **quote_mask)
{
	int	fields_len;
	char	**fields;
	int	index = 0;

	fields_len = get_fields_len(expand_strs, quote_mask);
	fields = malloc(sizeof(char *) * (fields_len + 1));
	fill_fields(expand_strs, fields, quote_mask);
	fields[fields_len] = NULL;
	while (fields[index])
		printf("[%s]\n", fields[index++]);
}
