#include <minishell.h>

bool	str_blank(char *str)
{
	size_t	index;
	size_t	space_count;
	
	index = 0;
	space_count = 0;
	while (str[index])
	{
		if (char_in_set(str[index], "\t\n "))
			space_count++;
		index++;
	}
	return (space_count == index);
}
