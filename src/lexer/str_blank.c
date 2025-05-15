#include <minishell.h>

// this function check if str has only spaces: newline, tab, blank_space
// and return true if so and false if not
// get [char *]
// return [bool]
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
