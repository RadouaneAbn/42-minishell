/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radouane <radouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:15:42 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/14 19:45:27 by radouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	free_elem_from_lvl(t_gc_level *level, void *data)
{
	t_gc_node	*node;
	t_gc_node	*tmp;

	if (!level || !data)
		return (1);
	node = level->aloc_list;
	if (node == NULL)
		return (1);
	tmp = NULL;
	if (data == node->data)
	{
		tmp = level->aloc_list;
		level->aloc_list = level->aloc_list->next;
	}
	else
		tmp = find_data(node, data);
	if (tmp != NULL)
	{
		free(tmp->data);
		free(tmp);
		return (0);
	}
	return (1);
}

void	gc_local_free(void *data)
{
	t_gc_level	*level;

	level = get_current_level();
	if (level)
		free_elem_from_lvl(level, data);
}

void	gc_global_free(void *data)
{
	t_gc_level	*level;

	level = get_current_level();
	if (level == NULL)
		return ;
	while (level && free_elem_from_lvl(level, data) != 0)
		level = level->parent;
}

void	free_to_lvl_zero(void)
{
	t_gc_level	*level;

	level = get_current_level();
	if (level == NULL)
		return ;
	while (get_current_level()->parent != NULL)
		free_level();
}

void	gc_free_from_level(void *data, int wanted_level)
{
	t_gc_level	*lvl;

	lvl = get_current_level();
	while (lvl)
	{
		if (lvl->id == wanted_level)
			break ;
		lvl = lvl->parent;
	}
	if (lvl->id == wanted_level)
		free_elem_from_lvl(lvl, data);
}
