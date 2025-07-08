#include <minishell.h>

size_t	get_strings_len(char **strings)
{
	size_t	len;

	if (strings == NULL)
		return (0);
	len = 0;
	while (strings[len])
		len++;
	return (len);
}
