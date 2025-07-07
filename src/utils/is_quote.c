#include <minishell.h>

bool	is_quote(char character)
{
	return (char_in_set(character, "\"'"));
}
