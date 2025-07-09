#include <minishell.h>

bool	has_unquoted_star(char *str, char *quote_mask, t_range range)
{
	size_t	index;

	index = 0;
	while (index < range.len)
	{
		if (!get_bit(quote_mask, range.start))
		{
			if (str[range.start] == '*' && !quoted_char(quote_mask, range.start))
					return (true);
			index++;
		}
		range.start++;
	}
	return (false);
}

void	cp_field(char *field, char *expand_str, char *quote_mask, t_range range, t_list **star_mask)
{
	size_t	index;
	size_t	start_tmp;
	bool	star_found;
	char	*star_mask_bits;
	t_list	*new_node;

	index = 0;
	star_found = false;
	start_tmp = range.start;
	star_mask_bits = NULL;
	if (has_unquoted_star(expand_str, quote_mask, range))
	{
			star_mask_bits = malloc(sizeof(char) * get_byte_len(range.len));
			star_found = true;
	}
	while (index < range.len)
	{
		if (!get_bit(quote_mask, range.start))
		{
			if (star_found)
			{
				if (expand_str[range.start] == '*' && !quoted_char(quote_mask, range.start))
					set_mask_bit(star_mask_bits, index, 1);
				else
					set_mask_bit(star_mask_bits, index, 0);
			}
			field[index] = expand_str[range.start];
			index++;
		}
		range.start++;
	}
	field[index] = '\0';
	if (star_found)
		shift_bits(star_mask_bits, index);
	new_node = ft_lstnew(star_mask_bits);
	ft_lstadd_back(star_mask, new_node);
	//print_bits(star_mask_bits, get_byte_len(index));
	//set_star_mask(field, star_mask, quote_mask, (t_range){start_tmp, index});
}


void	set_field(char **field, char *expand_str, char *quote_mask, t_range range, t_list **star_mask)
{
	*field = malloc(sizeof(char) * (range.len + 1));
	cp_field(*field, expand_str, quote_mask, range, star_mask);
}

void	fill_fields(char *expand_str, char **fields, char *quote_mask, t_list **star_mask)
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
			set_field(fields + fields_len, expand_str, quote_mask, (t_range){start, len}, star_mask);
			fields_len++;
		}
		else
			index++;
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
		star_mask = star_mask->next;
		index++;
	}
}

char	**field_splitting(char **expand_strs, char **quote_mask, t_list **star_mask)
{
	size_t	fields_len;
	char	**fields;

	fields_len = get_fields_len(*expand_strs, *quote_mask);
	if (fields_len == 0)
		return (NULL);
	fields = malloc(sizeof(char *) * (fields_len + 1));
	fill_fields(*expand_strs, fields, *quote_mask, star_mask);
	fields[fields_len] = NULL;
	//print_strings(fields, *star_mask);
	return (fields);
}
