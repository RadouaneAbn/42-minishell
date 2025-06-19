#include "../../include/libft.h"
#include "../../include/hash_map.h"
#include "../../include/utils.h"

t_map *get_map()
{
    static t_map *map;

    if (map == NULL)
    {
        map = malloc(sizeof(t_map));
        if (map == NULL)
            return (NULL);
        ft_bzero(map, sizeof(t_map));
    }

    return (map);
}

int export(char *key, char *value)
{
    t_map *map;

    map = get_map();
    if (map == NULL)
        return (-1);
    add_to_map(map, key, value);
    return (0);
}

char *expand(char *key)
{
    t_map *map;
    t_node *node;

    map = get_map();
    if (map == NULL)
        return (NULL);
    node = find_in_map(map, key);
    if (node)
        return (node->value);
    return ("");
}

void remove_from_map(t_map *map, char *key)
{
    int idx;
	t_node *current_node;
	t_node *prev;

	idx = index_key(key);
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

void remove_env_variable(t_map *map, char *key)
{
    t_node *wanted_node;

    wanted_node = find_in_map(map, key);
    if (wanted_node == NULL)
        return ;
    remove_from_ordered_list(map, key);
    remove_from_map(map, key);
    free(wanted_node->key);
	free(wanted_node->value);
	free(wanted_node);
}

int unset(char *key)
{
    t_map *map;
    
    map = get_map();
    if (map == NULL)
        return (1);
    remove_env_variable(map, key);
    return (0);
}
