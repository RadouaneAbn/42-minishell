#include <minishell.h>

int print_env()
{
    t_map *map;
    t_node *node;

    map = get_map();
    if (map == NULL)
        return (1);
    node = map->ordered_list;
    while (node)
    {
        if (node->value)
            printf("%s=%s\n", node->key, node->value);
        node = node->ordered_next;
    }
    return (1);
}

int print_exports()
{
    t_map *map;
    t_node *node;

    map = get_map();
    if (map == NULL)
        return (1);
    node = map->ordered_list;
    while (node)
    {
        printf("declare -x %s=%s\n", node->key, node->value);
        node = node->ordered_next;
    }
    return (1);
}
