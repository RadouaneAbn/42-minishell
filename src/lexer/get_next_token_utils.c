#include <minishell.h>

char	*get_operator(int index)
{
	static char	*fully[9];

	if (fully[0] == NULL)
	{
		fully[AND] = "&&";
		fully[OR] = "||";
		fully[HERE_DOC] = "<<";
		fully[APPEND_OUT] = ">>";
		fully[RED_IN] = "<";
		fully[RED_OUT] = ">";
		fully[PIPE] = "|";
		fully[L_PAREN] = "(";
		fully[R_PAREN] = ")";
	}
	return (fully[index]);
}

int	get_operator_type(char *line, size_t *position)
{
	size_t	len;
	char	*token_value;
	int		index;

	index = 0;
	while (index < 9)
	{
		token_value = get_operator(index);
		len = ft_strlen(token_value);
		if (strnmatch(line + *position, token_value, len))
			break ;
		index++;
	}
	return (index);
}

bool	token_is_operator(char *line, size_t position)
{
	size_t	len;
	char	*token_value;
	int		index;

	index = 0;
	while (index < 9)
	{
		token_value = get_operator(index);
		len = ft_strlen(token_value);
		if (strnmatch(line + position, token_value, len))
			return (true);
		index++;
	}
	return (false);
}

void	set_operator_token(t_token *token, char *line, size_t *position)
{
	size_t	len;
	int		index;
	int		is_operator;
	char	*token_value;

	is_operator = token_is_operator(line, *position);
	if (is_operator)
	{
		index = get_operator_type(line, position);
		token_value = get_operator(index);
		len = ft_strlen(token_value);
		token->type = index;
		token->lexeme = ft_strdup(token_value);
		*position += len;
		return ;
	}
}

void	set_word_token(t_token *token, char *line, size_t *position)
{
	bool	quoted;
	size_t	start;
	char	quote;

	quoted = false;
	start = *position;
	while (((!quoted && !(token_is_operator(line, *position)
						|| is_space(line[*position], "\t \n")))
				|| (quoted)) && line[*position] != '\0')
	{
		if (char_in_set(line[*position], "'\"") && !quoted)
		{
			quote = line[*position];
			quoted = true;
		}
		else if (char_in_set(line[*position], "'\"") && quote == line[*position])
			quoted = false;
		(*position)++;
	}
	if (start != *position)
	{
		token->lexeme = ft_substr(line, start, *position - start);
		token->type = WORD;
	}
	if (quoted)
		printf("WARNING: quote");
}
