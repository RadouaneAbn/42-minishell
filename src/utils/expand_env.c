#include <minishell.h>

char	*expand_env(char *key)
{
	if (strmatch(key, "var"))
		return ("$var");
	else if (strmatch(key, "blank"))
		return ("              ");
	else if (strmatch(key, "quote"))
		return ("\"");
	else if (strmatch(key, "cwd"))
		return ("hey hey hey");
	else if (strmatch(key, "but"))
		return ("");
	else if (strmatch(key, "var1"))
		return ("\"\"");
	else if (strmatch(key, "var2"))
		return ("'");
	else if (strmatch(key, "star"))
		return ("*");
	return ("");
}
