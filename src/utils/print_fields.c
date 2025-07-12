#include <minishell.h>

void	print_fields(char **fields, t_list *star_mask)
{
	size_t	index;

	index = 0;
	while (fields[index])
	{
		if (star_mask->content)
			print_bits(star_mask->content, get_byte_len(ft_strlen(fields[index])));
		star_mask = star_mask->next;
		index++;
	}
}
