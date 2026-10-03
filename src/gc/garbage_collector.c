/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radouane <radouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:11:55 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/14 22:19:45 by radouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_gc	**get_gc(void)
{
	static t_gc	*gc;
	static bool	init;

	if (gc == NULL && init == false)
	{
		gc = malloc(sizeof(t_gc));
		if (gc == NULL)
		{
			perror(GC_MALLOC);
			exit(1);
		}
		gc->current_level = NULL;
		gc->level_n = 0;
		init = true;
	}
	return (&gc);
}

t_gc_level	*gc_level_init(void)
{
	t_gc_level	*new_level;
	t_gc		*gc;

	gc = *get_gc();
	if (gc == NULL)
		return (NULL);
	new_level = malloc(sizeof(t_gc_level));
	if (new_level == NULL)
	{
		perror(GC_MALLOC);
		clean_exit(1);
	}
	new_level->aloc_list = NULL;
	new_level->parent = gc->current_level;
	gc->current_level = new_level;
	gc->current_level->id = gc->level_n;
	gc->level_n++;
	return (gc->current_level);
}

t_gc_level	*get_current_level(void)
{
	t_gc	*gc;

	gc = *get_gc();
	if (gc == NULL)
		return (NULL);
	return (gc->current_level);
}
