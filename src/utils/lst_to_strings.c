#include <minishell.h>

char	**lst_to_strings(t_list *list)
{
	char	**strings;
	size_t	lst_size;
	size_t	index;

	index = 0;
	lst_size = ft_lstsize(list);
	strings = malloc((lst_size + 1) * sizeof(char *));
	while(index < lst_size)
	{
		strings[index] = ft_strdup(list->content);
		list = list->next;
		index++;
	}
	strings[index] = NULL;
	return (strings);
}
