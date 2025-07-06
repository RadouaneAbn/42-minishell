#include <minishell.h>

void	set_mask_byte(char *quote_array, int size, char bit)
{
	int	byte_index;

	byte_index = size / 8;
	quote_array[byte_index] = (quote_array[byte_index] << 1) | bit;
}

void	expand(char *str, char *expand_str, char *quote_array)
{
	bool	quoted;
	char	quote;
	size_t	len;
	size_t	start;

	quoted = false;
	len = 0;
	start = 0;
	while (*str)
	{
		if (char_in_set(*str, "'\""))
		{
			if (!quoted)
				quote = *str;
			if (quote == *str)
			{
				set_mask_byte(quote_array, start, 1);
				start = len;
				start++;
				quoted = !quoted;
			}
		}
		if (((quoted && (quote == '"')) || !quoted) && *str == '$' && first_key_ch(peakch(str)))
			expand_word(&str, &len, expand_str);
		else
		{
			expand_str[len] = *str;
			len++;
			str++;
		}
		while (start < len)
		{
			set_mask_byte(quote_array, start, 0);
			start++;
		}
	}
	expand_str[len] = '\0';
}

char	*get_value(char *key)
{
	if (strmatch(key, "var"))
		return ("hey");
	else if (strmatch(key, "cwd"))
		return ("hey hey hey");
	else if (strmatch(key, "but"))
		return ("");
	else if (strmatch(key, "var1"))
		return ("\"\"");
	else if (strmatch(key, "var2"))
		return ("'");
	return ("");
}

void	expand_word(char **str, size_t *len, char *expand_str)
{
	int	exit_code_len;
	char	*exit_code;

	if (peakch(*str) == '?')
	{
		exit_code = "100";
		exit_code_len = ft_strlen(exit_code);
		ft_memcpy(expand_str + *len, exit_code, exit_code_len);
		*len += exit_code_len;
		(*str) += 2;
		//free(exit_code);
		return ;
	}
	(*str)++;
	char *key = get_key(str);
	if (key == NULL)
		return ;
	char *value = get_value(key);
	ft_memcpy(expand_str + *len, value, ft_strlen(value));
	//free(key);
	*len += ft_strlen(value);
}
