#include <minishell.h>

size_t	get_star_fields_len(char *str, char *star_mask)
{
	size_t	index;
	size_t	len;

	index = 0;
	len = 0;
	while (fields[index])
	{
		if (get_bit(str, index) && (!str[index + 1] || !get_bit(str, index + 1) ))
			len++;
		index++;
	}
	return (len);
}

void	define_star_field(char **parts, char *str, size_t *index, char *star_mask)
{
	size_t	start;
	size_t	*end;

	start = *index;
	end = index;
	while (get_bit(star_mask, end))
		end++;
	*index = end;
	*parts = ft_substr(str, start, end);
}

void	set_star_fields(char **parts, char *str, char *star_mask)
{
	size_t	index;
	size_t	field_index

	index = 0;
	field_index = 0;
	while (fields[index])
	{
		if (get_bit(str, index))
		{
			define_star_field(parts + field_index, str, &index, char *star_mask);
			field_index++;
		}
		else
			index++;
	}
	
}

char **get_star_fields(char *str, char *star_mask)
{
	size_t	len;
	char	**parts;

	len = get_star_fields_len(str, star_mask);
	parts = malloc(sizeof(char *) * (len + 1));
	set_star_fields(parts, str, star_mask);
	parts[len] = NULL;
}
