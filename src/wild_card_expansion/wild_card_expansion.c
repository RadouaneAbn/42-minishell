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
	if (filename[0] == '.' && pattern[0] != '.')
		return (false);
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
	if (strings[index] == NULL)
		return (true);
	return (false);
}

void	print_list(t_list *list)
{
	while (list)
	{
		printf("%s\n", (char *)list->content);
		list = list->next;
	}
}

void	get_child_files(char *dir, char **pattern, int number)
{
	//t_list	*list = NULL;
	struct dirent *child_file;
	DIR *pDir;
	char *folder;

	if (dir == NULL)
		pDir = opendir (".");
	else
		pDir = opendir (dir);
	while (pattern[number] && pDir && (child_file = readdir(pDir)) != NULL) {
		if (check_pattern(child_file->d_name, pattern[number]))
		{
			if (pattern[number + 1] == NULL)
			{
				if (dir == NULL)
					printf("[%s]\n", child_file->d_name);
				else
					printf("[%s]/[%s]\n", dir, child_file->d_name);
			}
			//ft_lstadd_back(&list, ft_lstnew(ft_strdup(child_file->d_name)));
			//if (strcmp(dir, ".") == 0)
				//folder = NULL;
			//else
			if (dir == NULL)
				folder = ft_strjoin(".", "/");
			else
				folder = ft_strjoin(dir, "/");
			get_child_files(ft_strjoin(folder, child_file->d_name), pattern, number + 1);
		}
	}
	closedir (pDir);
}

int main (int argc, char *argv[])
{
	char	**patterns;

	patterns = ft_split(argv[1], '/');
	if (argv[1][0] == '/')
		get_child_files("/", patterns, 0);
	else if (strcmp(patterns[0], ".") == 0 || strcmp(patterns[0], "..") == 0)
		get_child_files(patterns[0], patterns + 1, 0);
	else
		get_child_files(NULL, patterns, 0);
	return 0;
}
