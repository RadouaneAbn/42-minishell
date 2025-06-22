#include <minishell.h>

void remove_from_map(t_map *map, char *key)
{
    int idx;
	t_node *current_node;
	t_node *prev;

	idx = hash(key);
	current_node = map->map[idx];
    while (current_node)
	{
		if (ft_strcmp(current_node->key, key) == 0)
			break ;
		prev = current_node;
		current_node = current_node->next;
	}
    if (current_node == map->map[idx])
        map->map[idx] = map->map[idx];
    else
        prev->next = current_node->next;
}