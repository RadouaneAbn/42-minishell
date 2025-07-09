#include <minishell.h>

bool	is_removable_quote(char character, bool reset)
{
	static char		quote;
	static bool		quoted;

	if (!reset)
	{
		if (is_quote(character) && !quoted)
			quote = character;
		if (is_quote(character) && character == quote)
		{
			quoted = !quoted;
			return (true);
		}
	}
	else
	{
		quoted = false;
		quote = '\0';
	}
	return (false);
}
