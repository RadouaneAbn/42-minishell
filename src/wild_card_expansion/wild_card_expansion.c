#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include "libft.h"
char	get_last_char(char *str)
{
	size_t	index;

	index = 0;
	while (str[index])
	{
		if (str[index + 1] == '\0')
			return (str[index]);
		index++;
	}
	return (str[index]);
}

bool	check_pattern(char *filename, char *pattern)
{
	char	**strings;
	int	index;
	size_t	offset;
	size_t	start;

	index = 0;
	offset = 0;
	strings = ft_split(pattern, '*');
	while (filename[offset] && strings[index])
	{
		if ((index == 0 && pattern[0] != '*') && strncmp(filename, strings[index], ft_strlen(strings[index])) != 0)
			return (false);
		start = ft_strlen(filename) - ft_strlen(strings[index]);
		if (strings[index + 1] == NULL && get_last_char(pattern) != '*' && strncmp(filename + start, strings[index], ft_strlen(strings[index])) == 0)
			return (true);
		else if (strings[index + 1] == NULL && get_last_char(pattern) != '*')
			return (false);
		if (strncmp(filename + offset, strings[index], ft_strlen(strings[index])) == 0)
		{
			offset += ft_strlen(strings[index]);
			index++;
			continue ;
		}
		offset++;
	}
	int j;
	j = 0;
	if (strings[index] == NULL)
		return (true);
	return (false);
}

int main (int argc, char *argv[])
{
	struct dirent *child_file;
	DIR *pDir;
	char	*var = argv[1];

	pDir = opendir (".");
	while ((child_file = readdir(pDir)) != NULL) {
		if (check_pattern(child_file->d_name, var))
			printf("%s\n", child_file->d_name);
	}
	closedir (pDir);
	return 0;
}
