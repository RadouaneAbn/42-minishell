#include <minishell.h>

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
				set_mask_bit(star_mask, index, 1);
			else
				set_mask_bit(star_mask, index, 0);
			index++;
		}
		range.start++;
	}
	shift_bits(star_mask, range.len);
	return (star_mask);
}

bool	has_unquoted_star(char *quote_mask, char *str)
{
	size_t	index;

	index = 0;
	while (str[index])
	{
		if (str[index] == '*' && !quoted_char(quote_mask, index))
			return (true);
		index++;
	}
	return (false);
}

void	set_star_mask(char *field, t_list **star_mask, char *quote_mask, t_range range)
{
	char	*mask;
	t_list	*mask_node;

	if (has_unquoted_star(quote_mask, field))
	{
		printf("yes\n");
		mask = get_star_mask(field, quote_mask, range);
	}
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


void	set_field(char **field, char *expand_str, char *quote_mask, t_range range, t_list **star_mask)
{
	//printf("range len: %zu start: %zu char: %c\n", range.len, range.start, expand_str[range.start]);
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
		printf("[%s]\n", fields[index]);
		star_mask = star_mask->next;
		index++;
	}
}

char	**field_splitting(char **expand_strs, char **quote_mask, t_list **star_mask)
{
	size_t	fields_len;
	char	**fields;

	fields_len = get_fields_len(*expand_strs, *quote_mask);
	//printf("fields_len %zu\n", fields_len);
	if (fields_len == 0)
		return (NULL);
	fields = malloc(sizeof(char *) * (fields_len + 1));
	fill_fields(*expand_strs, fields, *quote_mask, star_mask);
	fields[fields_len] = NULL;
	//print_strings(fields, *star_mask);
	return (fields);
}
