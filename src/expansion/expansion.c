#include <minishell.h>

size_t	expand_word_len(char **str)
{
	size_t	len;
	char	*key;

	len = 0;
	if (peakch(*str) == '?')
	{
		len += ft_strlen("0");
		*str += 2;
		return (len);
	}
	if (!ft_isalpha(peakch(*str)) && peakch(*str) != '_')
	{
		(*str) += 2;
		return (2);
	}
	(*str)++;
	key = get_key(str);
	if (key == NULL)
		return (0);
	free(key);
	return (7);
}

//this function return the size of a str that has expanded words
//gets the string: (char *)
//returns len (size_t)
size_t	expand_str_len(char *str)
{
	bool	quoted;
	char	quote;
	size_t	len;

	quoted = false;
	len = 0;
	while (*str)
	{
		if (char_in_set(*str, "'\"") && !quoted)
			quote = *str;
		if (quote == *str)
			quoted = !quoted;
		if (!quoted && *str == '$' && char_in_set(peakch(str), "'\""))
			str++;
		else if (((quoted && (quote == '"')) || !quoted) && *str == '$' && peakch(str))
			len += expand_word_len(&str);
		else
		{
			len++;
			str++;
		}
	}
	return (len);
}
