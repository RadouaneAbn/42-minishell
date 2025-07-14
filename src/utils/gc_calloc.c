#include <minishell.h>

void *gc_calloc(size_t nmemb, size_t size)
{
	return (ft_calloc(nmemb, size));
}
