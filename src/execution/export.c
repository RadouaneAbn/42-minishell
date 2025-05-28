#include "../../include/libft.h"
#include "../../include/env.h"

int export(char *key, char *value)
{
    t_info *info;

    info = get_info();
    if (info == NULL)
        return (-1);
    add_to_map(&(info->exports), key, value);
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

int unset(char *key)
{
    t_map *map;
    
    map = get_map();
    if (map == NULL)
        return (-1);
    if (find_in_map(map, key) == NULL)
        return (0);
    remove_from_map(map, key);
}
