#include <minishell.h>

bool	is_space(char character)
{
	return (char_in_set(character, "\t\n "));
}
