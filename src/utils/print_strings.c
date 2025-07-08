#include <minishell.h>

void	print_strings(char **strings)
{
	size_t	index;

	if (strings == NULL)
	{
		printf("[NULL]\n");
		return ;
	}
	index = 0;
	while (strings[index])
	{
		printf("%zu: [%s]\n", index, strings[index]);
		index++;
	}
}
