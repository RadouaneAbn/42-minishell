#include <minishell.h>

bool	char_in_set(char c, char *set)
{
	size_t	index;

	index = 0;
	while (set[index])
	{
		if (c == set[index])
			return (true);
		index++;
	}
	return (false);
}
