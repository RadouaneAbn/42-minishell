/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:35:56 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/16 00:37:03 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHMAP_H
# define HASHMAP_H

# define MAP_SIZE 1024
# define TRUE 1
# define FALSE 0

typedef struct s_node	t_node;

struct					s_node
{
	char				*key;
	char				*value;
	t_node				*next;
	t_node				*ordered_next;
};

typedef struct s_map
{
	t_node				*map[MAP_SIZE];
	t_node				*ordered_list;
	int					size;
}						t_map;

unsigned int			hash(const char *key);
t_node					*create_new_node(char *key, char *value);
t_node					*find_in_map(t_map *map, char *key);
void					append_to_ordered_list(t_map *map, t_node *node);
int						add_to_map(t_map *map, char *key, char *value);
void					remove_from_map(t_map *map, char *key);
void					remove_from_ordered_list(t_map *map, char *key);
t_map					*get_map(void);
char					*copy_string(char *src);

#endif