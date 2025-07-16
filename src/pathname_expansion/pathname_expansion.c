/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathname_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:10:14 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/16 21:12:13 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

bool	match_pattern(char *filename, char *pattern,
		char *star_mask, char **star_fields)
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
	if (check_match_pattern(filename, star_fields))
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

void	get_match_patterns_childs(t_list **list, char *pattern, char *star_mask)
{
	struct dirent	*child_file;
	DIR				*parent_dir;
	bool			match_found;
	char			**star_fields;

	match_found = false;
	parent_dir = opendir (".");
	star_fields = get_star_fields(pattern, star_mask);
	child_file = readdir(parent_dir);
	while (parent_dir && child_file)
	{
		if (match_pattern(child_file->d_name, pattern, star_mask, star_fields))
		{
			match_found = true;
			ft_lstadd_back(list, ft_lstnew(ft_strdup(child_file->d_name)));
		}
	}
	if (!match_found)
		ft_lstadd_back(list, ft_lstnew(ft_strdup(pattern)));
	closedir (parent_dir);
	free_strings(star_fields);
	child_file = readdir(parent_dir);
}

t_list	*pathname_expansion(char **fields, t_list *star_mask)
{
	t_list	*list;
	size_t	index;

	list = NULL;
	index = 0;
	while (fields[index])
	{
		if (star_mask->content)
			get_match_patterns_childs(&list, fields[index], star_mask->content);
		else
			ft_lstadd_back(&list, ft_lstnew(ft_strdup(fields[index])));
		star_mask = star_mask->next;
		index++;
	}
	return (list);
}
