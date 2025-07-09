#include <minishell.h>

bool	is_space(char c, char *spaces)
{
	size_t	index;

	index = 0;
	while (spaces[index])
	{
		if (c == spaces[index])
			return (true);
		index++;
	}
	return (false);
}
