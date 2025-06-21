#include <minishell.h>

//check if char in word after $ is valid
bool	valid_key_char(char c)
{
	return (ft_isalpha(c) || ft_isdigit(c) || c == '_');
}

char	*get_key(char **str)
{
	char	*key;
	size_t	len;

	len = 0;
	while (valid_key_char((*str)[len]))
		len++;
	key = ft_substr(*str, 0, len);
	if (key == NULL)
		return (NULL);
	*str += len;
	return (key);
}
