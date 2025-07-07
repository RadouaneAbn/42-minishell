#include <minishell.h>

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

void	get_child_files(t_tree **tree, char *pattern)
{
	struct dirent *child_file;
	DIR *pDir;
	bool	match_found;

	match_found = false;
		pDir = opendir (".");
	while (pDir && (child_file = readdir(pDir)) != NULL) {
		if (check_pattern(child_file->d_name, pattern))
		{
			match_found = true;
			//ft_lstadd_back(wild_card_list, ft_lstnew(ft_strdup(child_file->d_name)));
			tree_add_back(tree, tree_create_new(0, ft_strdup(child_file->d_name)));
		}
	}
	if (!match_found)
			tree_add_back(tree, tree_create_new(0, pattern));
	//ft_lstadd_back(wild_card_list, ft_lstnew(ft_strdup(pattern)));
	closedir (pDir);
}


t_tree	*wild_card_expansion(char **fields, t_list *star_mask)
{
	t_tree	*tree;
	size_t	index;

	tree = NULL;
	index = 0;
	while (fields[index])
	{
		if (star_mask->content)
			get_child_files(&tree, fields[index]);
		else
			tree_add_back(&tree, tree_create_new(0, fields[index]));
		index++;
	}
	return (tree);
}
