#include <minishell.h>

int print_env(int fd)
{
    t_map *map;
    t_node *node;

    map = get_map();
    if (map == NULL)
        return (1);
    if (fd == -1)
        fd = STDOUT_FILENO;
    node = map->ordered_list;
    while (node)
    {
        if (node->value)
        {
            ft_putstr_fd(node->key, fd);
            ft_putstr_fd("=", fd);
            ft_putstr_fd(node->key, fd);
            ft_putstr_fd("\n", fd);
        }
        node = node->ordered_next;
    }
    return (0);
}

int print_exports(int fd)
{
    t_map *map;
    t_node *node;

    map = get_map();
    if (map == NULL)
        return (EXIT_FAILURE);
    if (fd == -1)
        fd = STDOUT_FILENO;
    node = map->ordered_list;
    while (node)
    {
        ft_putstr_fd("declare -x ", fd);
        ft_putstr_fd(node->key, fd);
        if (node->value)
        {
            ft_putstr_fd("=\"", fd);
            ft_putstr_fd(node->key, fd);
            ft_putstr_fd("\"", fd);
        }
        ft_putstr_fd("\n", fd);
        node = node->ordered_next;
    }
    return (EXIT_SUCCESS);
}
