#include <minishell.h>

//NOTE: you can use something like a struct that has members: value and type
//and those values will be the actuall values like && not the enum
//the type is the enum and you can use it to return the type and compare the value
//with the struct value

void	get_token(t_token *token, char *line, size_t *position)
{
	while (char_in_set(line[*position], "\t \n"))
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
