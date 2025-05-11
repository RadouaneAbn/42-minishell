#include <lexer.h>

void	print_token(t_token token)
{
	char *types[] = {
		"AND",
		"OR",
		"HERE_DOC",
		"APPEND_OUT",
		"RED_IN",
		"RED_OUT",
		"PIPE",
		"L_PAREN",
		"R_PAREN",
		"WORD"
	};

	printf("token ["GREEN"%s"RESET"] token type: "BLUE"%s\n"RESET, token.lexeme, types[token.type]);
}
