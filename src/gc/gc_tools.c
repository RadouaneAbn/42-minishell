/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:12:05 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/10 19:32:46 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <garbage_collector.h>

void	level_down(void)
{
	t_gc	*gc;

	gc = *get_gc();
	if (!gc || !gc->current_level)
		return ;
	gc->current_level = gc->current_level->parent;
	gc->level_n--;
}

void	free_level(void)
{
	t_gc		*gc;
	t_gc_level	*current_level;
	t_gc_node	*node;
	t_gc_node	*tmp;

	gc = *get_gc();
	if (!gc || !gc->current_level)
		return ;
	current_level = get_current_level();
	// printf("freeing level %d\n", current_level->id);
	node = current_level->aloc_list;
	while (node)
	{
		tmp = node;
		node = node->next;
		free(tmp->data);
		free(tmp);
	}
	level_down();
	free(current_level);
}

void	free_gc(void)
{
	t_gc	**gc;

	gc = get_gc();
	if (*gc == NULL || (*gc)->current_level != NULL)
		return ;
	free(*gc);
	*gc = NULL;
}

void	free_full(void)
{
	t_gc		*gc;

	gc = *get_gc();
	if (gc == NULL)
		return ;
	while (gc->current_level)
		free_level();
	free_gc();
}

t_gc_node	*find_data(t_gc_node *head, void *data)
{
	t_gc_node	*tmp;

	tmp = NULL;
	while (head->next)
	{
		if (head->next->data == data)
		{
			tmp = head->next;
			head->next = head->next->next;
			break ;
		}
		head = head->next;
	}
	return (tmp);
}
