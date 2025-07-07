#include <minishell.h>

bool	strnmatch(const char *string_1, const char *string_2, size_t n)
{
	return (ft_strncmp(string_1, string_2, n) == 0);
}


