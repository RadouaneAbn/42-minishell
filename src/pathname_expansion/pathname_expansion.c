#include <minishell.h>

bool	check_match_pattern(char *filename, char **star_fields)
{
	size_t	offset;
	size_t	len;
	size_t	index;

	index = 0;
	offset = 0;
	while (filename[offset] && star_fields[index])
	{
		len = ft_strlen(star_fields[index]);
		if (strnmatch(filename + offset, star_fields[index], len))
		{
			offset += len;
			index++;
			continue ;
		}
		offset++;
	}
	return (star_fields[index] == NULL);
}

bool	match_pattern(char *filename, char *pattern, char *star_mask, char **star_fields)
{
	size_t	len;
	size_t	last;
	size_t	start;

	if (star_fields == NULL && filename[0] != '.')
		return (true);
	if (filename[0] == '.' && pattern[0] != '.')
		return (false);
	len = ft_strlen(*star_fields);
	if (!get_bit(star_mask, 0) && !strnmatch(filename, *star_fields, len))
		return (false);
	if (check_match_pattern(filename,  star_fields))
	{
		last = get_strings_len(star_fields) - 1;
		len = ft_strlen(star_fields[last]);
		start = ft_strlen(filename) - len;
		if (!get_bit(star_mask, ft_strlen(pattern) - 1)
			&& strnmatch(filename + start, star_fields[last], len))
			return (true);
		else if (!get_bit(star_mask, ft_strlen(pattern) - 1))
			return (false);
		return (true);
	}
	return (false);
}

void	get_match_patterns_childs(t_tree **tree, char *pattern, char *star_mask)
{
	struct dirent *child_file;
	DIR *parent_dir;
	bool	match_found;
	char **star_fields;

	match_found = false;
	parent_dir = opendir (".");
	star_fields = get_star_fields(pattern, star_mask);
	while (parent_dir && (child_file = readdir(parent_dir)) != NULL) {
		if (match_pattern(child_file->d_name, pattern, star_mask, star_fields))
		{
			match_found = true;
			tree_add_back(tree, tree_create_new(0, ft_strdup(child_file->d_name)));
		}
	}
	if (!match_found)
			tree_add_back(tree, tree_create_new(0, pattern));
	closedir (parent_dir);
	free_strings(star_fields);
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
