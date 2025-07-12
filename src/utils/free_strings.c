#include <minishell.h>

void gc_global_free(void *ptr)
{
	free(ptr);
}

void	free_strings(char **strings)
{
	size_t	index;

	if (strings == NULL)
		return ;
	index = 0;
	while (strings[index])
	{
		gc_global_free(strings[index]);
		index++;
	}
	gc_global_free(strings);;
}
