/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radouane <radouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:15:37 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/14 22:21:23 by radouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	*gc_save(void *data, t_gc_level *level)
{
	t_gc_node	*node;

	if (level == NULL)
		level = get_current_level();
	if (level == NULL)
		return (NULL);
	node = malloc(sizeof(t_gc_node));
	if (node == NULL)
	{
		perror(GC_MALLOC);
		clean_exit(1);
	}
	node->data = data;
	node->next = level->aloc_list;
	level->aloc_list = node;
	return (node);
}

void	*gc_malloc(size_t size)
{
	void	*data;

	data = malloc(size);
	if (data == NULL)
	{
		perror(GC_MALLOC);
		clean_exit(1);
	}
	if (gc_save(data, get_current_level()) == NULL)
	{
		free(data);
		clean_exit(1);
	}
	return (data);
}

void	*gc_calloc(size_t nmemb, size_t size)
{
	void	*data;

	data = ft_calloc(nmemb, size);
	if (data == NULL)
	{
		perror(GC_MALLOC);
		clean_exit(1);
	}
	return (data);
}

void	*gc_malloc_lvl(size_t size, int wanted_level)
{
	t_gc_level	*lvl;
	void		*data;

	lvl = get_current_level();
	while (lvl)
	{
		if (lvl->id == wanted_level)
			break ;
		lvl = lvl->parent;
	}
	if (lvl->id == wanted_level)
	{
		data = malloc(size);
		if (data == NULL)
		{
			perror(GC_MALLOC);
			clean_exit(1);
		}
		gc_save(data, lvl);
		return (data);
	}
	return (NULL);
}
