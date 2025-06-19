#include "../include/libft.h"
#include "../include/hash_map.h"
#include "../include/utils.h"
#include "../include/built_in.h"
#include "tests.h"

#define BUFFER_SIZE 1024

void free_arr(char **arr)
{
    int i = 0;

    if (arr == NULL)
        return ;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

void print_args(char **args)
{
    int i;

    i = 0;
    if (args == NULL)
        return;
    while (args[i])
    {
        printf("\"%3d\"> \"%s\"\n", i + 1, args[i]);
        i++;
    }
}

void print_env()
{
    t_map *map = get_map();
    if (map == NULL)
    {
        printf("map is null");
        return ;
    }
    t_node *node = map->ordered_list;

    while (node)
    {
        printf("%s=%s\n", node->key, node->value);
        node = node->ordered_next;
    }
}

void free_node(t_node *node)
{
    free(node->key);
    free(node->value);
    free(node);
}

void free_ordered_list(t_map *map)
{
    t_node *node = map->ordered_list;
    t_node *tmp;

    while (node)
    {
        tmp = node;
        node = node->ordered_next;
        free_node(tmp);
    }
}

void free_map()
{
    t_map *map = get_map();
    if (map == NULL)
    {
        printf("map is null");
        return ;
    }
    free_ordered_list(map);
    free(map);
}

int main()
{
    char buffer[BUFFER_SIZE];
    ssize_t s;
    char **args;
    char **var;
    int run = TRUE;

    while (run)
    {
        s = read(STDIN_FILENO, buffer, BUFFER_SIZE);
        if (s < 0)
            break;
        else if (s < 2)
            continue;
        buffer[s - 1] = 0;
        args = ft_split(buffer, ' ');
        if (args[1])
            var = ft_split(args[1], '=');
        else
            var = NULL;
        if (ft_strcmp(args[0], "export") == 0 && var)
            export(var[0], var[1]);
        else if (ft_strcmp(args[0], "unset") == 0)
            unset(var[0]);
        else if (ft_strcmp(args[0], "env") == 0)
            print_env();
        else if (ft_strcmp(args[0], "exit") == 0)
            run = FALSE;
        else
            printf("command not found!\n");
        free_arr(args);
        free_arr(var);
    }

    free_map();
}