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

size_t	get_fields_len(char *expand_str, char *quote_mask)
{
	size_t	field_len;
	size_t	index;
	bool current_ch_quoted;
	bool next_ch_quoted;

	field_len = 0;
	index = 0;
	while (expand_str[index])
	{
		current_ch_quoted = quoted_char(quote_mask, index);
		if (expand_str[index + 1])
			next_ch_quoted = quoted_char(quote_mask, index + 1);
		else
			next_ch_quoted = false;
		if ((current_ch_quoted || (!current_ch_quoted && !is_space(expand_str[index])))
				&& ((is_space(expand_str[index + 1]) && !next_ch_quoted) || !expand_str[index + 1]))
			field_len++;
		index++;
	}
	return (field_len);
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
