#include "test.h"

void load_env(char **env)
{
    int i;

    i = 0;
    while (env[i])
        pre_export(env[i++]);
}

void env_exist_in_my_env(t_map *map, char *var, t_status *status)
{
    char **arr;
    t_node *node;

    arr = split_export_args(var);
    node = find_in_map(map, arr[0]);
    if (node == NULL)
    {
        printf("Key: [%s] Not found in env\n", arr[0]);
        status->failure++;
    }
    else if (ft_strcmp(node->value, arr[1]) != 0)
    {
        printf("value error: [%s] != [%s]\n", arr[1], node->value);
        status->failure++;
    }
    else
        status->success++;
}

t_status check_env(char **env)
{
    t_status status;
    t_map *map;
    int i;

    i = 0;
    map = get_map();
    status.failure = 0;
    status.success = 0;
    while (env[i])
    {
        env_exist_in_my_env(map, env[i], &status);
        i++;
    }

    return (status);
}

void print_total_result(t_status status)
{
    printf("Total: [S: %d, F: %d]\n", status.success, status.failure);
}

void print_env_r(char **env)
{
    t_node *node;
    int i;

    i = 0;
    if (env == NULL)
    {
        node = get_map()->ordered_list;
        while (node)
        {
            printf("%s=%s\n", node->key, node->value);
            node = node->ordered_next;
        }
    }
    else
    {
        while (env[i])
            printf("%s\n", env[i++]);
    }
}

void debug_hashmap()
{
    t_map *map = get_map();;
    t_node **hashmap = map->map;
    t_node *node;
    int i;

    i = 0;
    while (i < MAP_SIZE)
    {
        node = hashmap[i];
        printf("%-3d: ", i);
        while (node)
        {
            printf("[%s] -> ", node->key);
            node = node->ordered_next;
        }
        printf("[null]\n");
        i++;
    }
}

void test_export(char **env)
{
    t_status status;
    t_status tmp;

    status.failure = 0;
    status.success = 0;

    load_env(env);

    // print_env_r(env);
    // printf("\n\n");
    // print_env_r(NULL);
    tmp = check_env(env);

    status.failure += tmp.failure;
    status.success += tmp.success;

    print_total_result(status);
    // debug_hashmap();
}