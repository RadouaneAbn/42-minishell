#include <minishell.h>

//NOTES: these function return 1 if s1 == s2 within the len n in the case of strnmatch
// and 0 if not (very basic but powerful)

bool	strnmatch(const char *s1, const char *s2, size_t n)
{
	return (ft_strncmp(s1, s2, n) == 0);
}

bool	strmatch(const char *s1, const char *s2)
{
	return (ft_strcmp(s1, s2) == 0);
}
