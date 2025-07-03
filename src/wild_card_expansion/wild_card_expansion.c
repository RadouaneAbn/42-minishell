#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include "libft.h"

bool	check_pattern(char *filename, char *pattern)
{
	char	**strings;
	int	index;
	size_t	offset;

	index = 0;
	offset = 0;
	strings = ft_split(pattern, '*');
	while (filename[offset] && strings[index])
	{
			if (strncmp(filename, strings[index], ft_strlen(strings[index])) == 0)
				index++;
			offset++;
	}
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
