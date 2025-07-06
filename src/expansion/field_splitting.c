#include <minishell.h>

bool	quoted_char(char *quote_mask, size_t size)
{
	size_t	index;
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

size_t	get_fields_len(char **expand_strs, char **quote_mask)
{
	size_t	field_len;
	size_t str_index;
	size_t	index;
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
			if (expand_strs[str_index][index + 1])
				next_ch_quoted = quoted_char(quote_mask[str_index], index + 1);
			else
				next_ch_quoted = false;
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


char *get_star_mask (char *field, char *quote_mask, size_t start, size_t	len)
{
	char	*star_mask;
	size_t	index;

	index = 0;
	star_mask = malloc(get_byte_len(len) * sizeof(char));
	while (index < len)
	{
		if (!get_bit(quote_mask, start))
		{
			if (!quoted_char(quote_mask, start) && field[index] == '*')
				set_mask_byte(star_mask, index, 1);
			else
				set_mask_byte(star_mask, index, 0);
			index++;
		}
		start++;
	}
	shift_bits(star_mask, len);
	return (star_mask);
}

void	set_star_mask(char *field, t_list **star_mask, char *quote_mask, size_t start_tmp, size_t	len)
{
	char	*mask;
	t_list	*mask_node;

	if (ft_strchr(field, '*'))
		mask = get_star_mask(field, quote_mask, start_tmp, len);
	else
		mask = NULL;
	mask_node = ft_lstnew(mask);
	ft_lstadd_back(star_mask, mask_node);
}

void	cp_field(char *field, char *expand_str, char *quote_mask, size_t start, size_t end, t_list **star_mask)
{
	size_t	index;
	size_t	start_tmp;

	index = 0;
	start_tmp = start;
	while (start < end)
	{
		if (!get_bit(quote_mask, start))
		{
			field[index] = expand_str[start];
			index++;
		}
		start++;
	}
	field[index] = '\0';
	set_star_mask(field, star_mask, quote_mask, start_tmp, start);
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

void	set_field(char **field, char *expand_str, char *quote_mask, size_t start, size_t end, t_list **star_mask)
{
	size_t	len;

	len = get_field_len(expand_str, quote_mask);
	*field = malloc(sizeof(char) * (len + 1));
	cp_field(*field, expand_str, quote_mask, start, end, star_mask);
}

void	fill_fields(char **expand_strs, char **fields, char **quote_mask, t_list **star_mask)
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

				set_field(fields + field_index, expand_strs[str_index], quote_mask[str_index], start, index + 1, star_mask);
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

void	print_fields(char **fields, t_list **star_mask)
{
	size_t	index;

	index = 0;
	while (fields[index])
	{
		if (star_mask->content)
			print_bits(star_mask->content, get_byte_len(ft_strlen(fields[index])));
		printf("[%s]\n", fields[index]);
		star_mask = star_mask->next;
		index++;
	}
}

void	filed_splitting(char **expand_strs, char **quote_mask)
{
	size_t	fields_len;
	char	**fields;
	t_list *star_mask;

	star_mask = NULL;
	fields_len = get_fields_len(expand_strs, quote_mask);
	fields = malloc(sizeof(char *) * (fields_len + 1));
	fill_fields(expand_strs, fields, quote_mask, &star_mask);
	fields[fields_len] = NULL;
}
