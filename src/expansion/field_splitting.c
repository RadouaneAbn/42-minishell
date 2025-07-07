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
			if ((current_ch_quoted || (!current_ch_quoted && !is_space(expand_strs[str_index][index])))
					&& ((is_space(expand_strs[str_index][index + 1]) && !next_ch_quoted) || !expand_strs[str_index][index + 1]))
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


char *get_star_mask (char *field, char *quote_mask, t_range range)
{
	char	*star_mask;
	size_t	index;

	index = 0;
	star_mask = malloc(get_byte_len(range.len) * sizeof(char));
	while (index < range.len)
	{
		if (!get_bit(quote_mask, range.start))
		{
			if (!quoted_char(quote_mask, range.start) && field[index] == '*')
				set_mask_byte(star_mask, index, 1);
			else
				set_mask_byte(star_mask, index, 0);
			index++;
		}
		range.start++;
	}
	shift_bits(star_mask, range.len);
	return (star_mask);
}

void	set_star_mask(char *field, t_list **star_mask, char *quote_mask, t_range range)
{
	char	*mask;
	t_list	*mask_node;

	if (ft_strchr(field, '*'))
		mask = get_star_mask(field, quote_mask, range);
	else
		mask = NULL;
	mask_node = ft_lstnew(mask);
	ft_lstadd_back(star_mask, mask_node);
}

void	cp_field(char *field, char *expand_str, char *quote_mask, t_range range, t_list **star_mask)
{
	size_t	index;
	size_t	start_tmp;

	index = 0;
	start_tmp = range.start;
	while (index < range.len)
	{
		if (!get_bit(quote_mask, range.start))
		{
			field[index] = expand_str[range.start];
			index++;
		}
		range.start++;
	}
	field[index] = '\0';
	set_star_mask(field, star_mask, quote_mask, (t_range){start_tmp, index});
}

size_t	get_field_len(char *expand_str, char *quote_mask, size_t *start)
{
	size_t	len;

	len = 0;
	while (expand_str[*start] && !(is_space(expand_str[*start])
			&& !quoted_char(quote_mask, *start)))
	{
		if (!get_bit(quote_mask, *start))
			len++;
		(*start)++;
	}
	return (len);
}

void	set_field(char **field, char *expand_str, char *quote_mask, t_range range, t_list **star_mask)
{
	//printf("range len: %zu start: %zu char: %c\n", range.len, range.start, expand_str[range.start]);
	*field = malloc(sizeof(char) * (range.len + 1));
	cp_field(*field, expand_str, quote_mask, range, star_mask);
}

void	fill_fields(char **expand_strs, char **fields, char **quote_mask, t_list **star_mask)
{
	size_t	str_index;
	size_t index;
	size_t	field_index;
	size_t	start;
	size_t	len;

	str_index = 0;
	field_index = 0;
	while (expand_strs[str_index])
	{
		index = 0;
		while (expand_strs[str_index][index])
		{
			if (expand_strs[str_index][index] && !(is_space(expand_strs[str_index][index])
					&& !quoted_char(quote_mask[str_index], index)))
			{
				start = index;
				len = get_field_len(expand_strs[str_index], quote_mask[str_index], &index);
				set_field(fields + field_index, expand_strs[str_index], quote_mask[str_index], (t_range){start, len}, star_mask);
				field_index++;
			}
			else
				index++;
		}
		str_index++;
	}
}

void	print_fields(char **fields, t_list *star_mask)
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

void	print_star_list(char **parts)
{
	size_t	index;

	index = 0;
	while (parts[index])
	{
		printf("[%s]\n", parts[index]);
		index++;
	}
}

char	**field_splitting(char **expand_strs, char **quote_mask)
{
	size_t	fields_len;
	char	**fields;
	t_list *star_mask;

	star_mask = NULL;
	fields_len = get_fields_len(expand_strs, quote_mask);
	fields = malloc(sizeof(char *) * (fields_len + 1));
	fill_fields(expand_strs, fields, quote_mask, &star_mask);
	fields[fields_len] = NULL;
	print_fields(fields, star_mask);
	//char **parts = get_star_fields(fields[0], star_mask->content);
	//print_star_list(parts);
	//(void)parts;
	return (fields);
}
