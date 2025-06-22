#include <minishell.h>

char *expand_env(char *key)
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
