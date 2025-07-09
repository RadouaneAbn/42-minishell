#include <minishell.h>

bool	match_pattern(char *filename, char *pattern, char *star_mask)
{
	char	**strings;
	int	index;
	(void)star_mask;
	size_t	offset;
	size_t	start;

	index = 0;
	offset = 0;
	strings = get_star_fields(pattern, star_mask);
	if (filename[0] == '.' && pattern[0] != '.')
		return (false);
	while (filename[offset] && strings[index])
	{
		if ((index == 0 && !get_bit(star_mask, 0)) && strncmp(filename, strings[index], ft_strlen(strings[index])) != 0)
			return (false);
		start = ft_strlen(filename) - ft_strlen(strings[index]);
		if (strings[index + 1] == NULL && !get_bit(star_mask, ft_strlen(pattern) - 1) && strncmp(filename + start, strings[index], ft_strlen(strings[index])) == 0)
			return (true);
		else if (strings[index + 1] == NULL && !get_bit(star_mask, ft_strlen(pattern) - 1))
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

void	get_match_patterns_childs(t_tree **tree, char *pattern, char *star_mask)
{
	struct dirent *child_file;
	DIR *pDir;
	bool	match_found;

	match_found = false;
		pDir = opendir (".");
	while (pDir && (child_file = readdir(pDir)) != NULL) {
		if (match_pattern(child_file->d_name, pattern, star_mask))
		{
			match_found = true;
			tree_add_back(tree, tree_create_new(0, ft_strdup(child_file->d_name)));
		}
	}
	if (!match_found)
			tree_add_back(tree, tree_create_new(0, pattern));
	closedir (pDir);
}

t_tree	*pathname_expansion(char **fields, t_list *star_mask)
{
	t_tree	*tree;
	size_t	index;

	tree = NULL;
	index = 0;
	while (fields[index])
	{
		if (star_mask->content)
			get_match_patterns_childs(&tree, fields[index], star_mask->content);
		else
			tree_add_back(&tree, tree_create_new(0, fields[index]));
		star_mask = star_mask->next;
		index++;
	}
	return (tree);
}
