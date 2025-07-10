/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:32:55 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/10 19:28:47 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define GC_MALLOC "minishell: garbage collector"

typedef struct s_gc_node
{
	void				*data;
	struct s_gc_node	*next;
}						t_gc_node;

typedef struct s_gc_level
{
	t_gc_node			*aloc_list;
	struct s_gc_level	*parent;
	int					id;
}						t_gc_level;

typedef struct s_gc
{
	t_gc_level			*current_level;
	int					level_n;
}						t_gc;

t_gc					**get_gc(void);
t_gc_level				*get_current_level(void);
void					*gc_save(void *data, t_gc_level *level);
void					level_down(void);

/* Garbage collector main functions */
t_gc_level				*gc_level_init(void);
void					free_level(void);
void					free_gc(void);
void					free_full(void);
void					*gc_malloc(size_t size);
void					gc_local_free(void *data);
void					gc_global_free(void *data);
void					free_to_lvl_zero(void);
void					gc_free_from_level(void *data, int wanted_level);
void					*gc_malloc_lvl(size_t size, int wanted_level);
void					*gc_calloc(size_t size);
t_gc_node	*find_data(t_gc_node *head, void *data);
/* Debug */
int						gc_status(void);
int						get_level(void);

#endif