#include <minishell.h>

void	get_token(t_token *token, char *line, size_t *position)
{
	while (is_space(line[*position]))
		*position += 1;
	if (line[*position])
	{
	if (token_is_operator(line, *position))
		set_operator_token(token, line, position);
	else
		set_word_token(token, line, position);
	}
}

void	get_next_token(t_token *token, char *line)
{
	static size_t	index;

	get_token(token, line, &index);
	if (token->lexeme == NULL)
		index = 0;
}
