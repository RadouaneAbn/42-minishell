#include <minishell.h>

size_t	expand_word_len(char **str)
{
	size_t	len;
	char	*key;
	int	exit_code_len;
	char	*exit_code;

	len = 0;
	if (peakch(*str) == '?')
	{
		exit_code = "100";
		exit_code_len = ft_strlen(exit_code);
		len += exit_code_len;
		*str += 2;
		//free(exit_code);
		return (len);
	}
	(*str)++;
	key = get_key(str);
	char *value = get_value(key);
	if (key == NULL)
		return (0);
	//free(key);
	return (ft_strlen(value));
}

size_t	expand_str_len(char *str)
{
	bool	quoted;
	char	quote;
	size_t	len;

	quoted = false;
	len = 0;
	while (*str)
	{
		if (is_quote(*str))
		{
			if (!quoted)
				quote = *str;
			if (quote == *str)
				quoted = !quoted;
		}
		if (((quoted && (quote == '"')) || !quoted) && *str == '$' && first_key_ch(peakch(str)))
			len += expand_word_len(&str);
		else
		{
			len++;
			str++;
		}
	}
	return (len);
}
