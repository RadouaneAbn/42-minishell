#include <minishell.h>

void	expand(char *str)
{
	bool	quoted;
	char	quote;
	size_t	index;

	index = 0;
	quoted = false;
	while (str[index])
	{
		if (char_in_set(str[index], "'\"") && !quoted)
			quote = str[index];
		if (quote == str[index])
			quoted = (quoted + 1) % 2;

		if (!quoted && str[index] == '$' && char_in_set(str[index + 1], "'\""))
			index++;
		else if (((quoted && (quote == '"')) || !quoted) && str[index] == '$' && str[index + 1])
			expand_word(str, &index);

		else
		{
			printf("%c", str[index]);
			index++;
		}
	}
}

bool	valid_key_char(char c)
{
	return (ft_isalpha(c) || ft_isdigit(c) || c == '_');
}

//to do: you have to handle "$"
void	expand_word(char *str, size_t *index)
{
	if (!ft_isalpha(str[*index + 1]) && str[*index + 1] != '_')
	{
		printf("%c%c", str[*index], str[*index + 1]);	
		*(index) += 2;
		return ;
	}
	(*index)++;
	printf("["BLUE"expand: ");
	while (str[*index])
	{
		if (valid_key_char(str[*index]))
			printf("%c", str[*index]);
		else
			break;
		(*index)++;
	}
	printf(RESET"]");
}
