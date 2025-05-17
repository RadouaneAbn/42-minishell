#include <lexer.h>

void	lexer(char *line)
{
	t_token	*token;

	while (true)
	{
		token = NULL;
		get_next_token(&token, line);
		if (token == NULL)
			break ;
		print_token(*token);
		free(token->lexeme);
		free(token);
	}
}
