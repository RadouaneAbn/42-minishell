#include <minishell.h>

void *gc_malloc(size_t size)
{
	return (malloc(size));
}
