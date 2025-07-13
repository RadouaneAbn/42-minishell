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
    printf("\n> Total <: [S: %d, F: %d]\n\n", status.success, status.failure);
}

void print_result(t_status status)
{
    printf("\nResult: [S: %d, F: %d]\n\n", status.success, status.failure);
}

t_status test_existing_var(void)
{
    char *test_env[] = {
        "USER_1=HAMZA",
        "ZSH=RED",
        "a=b",
        "b=",
        "c",
        NULL
    };
    int i;
    t_map *map;
    char **arr;
    char *value;
    t_status status;

    printf("Test expand existing values:\n");
    status.failure = 0;
    status.success = 0;
    i = 0;
    map = get_map();
    while (test_env[i])
    {
        arr = split_export_args(test_env[i]);
        pre_export(test_env[i]);
        value = expand_env(arr[0]);
        if (ft_strcmp(value, arr[1]) != 0)
        {
            printf("expand:\n\texpected: [%s]\n\tgot     : [%s]\n", arr[1], value);
            status.failure++;
        }
        else
            status.success++;
        i++;
    }
    return (status);
}

t_status test_non_existing_var(void)
{
    char *test_env[] = {
        "NON_EXISTING_VAR",
        "ZZSH",
        "aa",
        NULL
    };
    int i;
    t_map *map;
    char *value;
    t_status status;

    printf("Test expand non existing values:\n");
    status.failure = 0;
    status.success = 0;
    i = 0;
    map = get_map();
    while (test_env[i])
    {
        value = expand_env(test_env[i]);
        if (ft_strcmp(value, "") != 0)
        {
            printf("expand:\n\texpected: [%s]\n\tgot     : [%s]\n", "", value);
            status.failure++;
        }
        else
            status.success++;
        i++;
    }
    return (status);
}

t_status test_updating_existing_keys(void)
{
    char *test_env[] = {
        "USER=radouane",
        "ZSH=minishell",
        NULL
    };
    int i;
    t_map *map;
    char **arr;
    char *value;
    t_status status;

    printf("Test updating existing values:\n");
    status.failure = 0;
    status.success = 0;
    i = 0;
    map = get_map();
    while (test_env[i])
    {
        arr = split_export_args(test_env[i]);
        pre_export(test_env[i]);
        value = expand_env(arr[0]);
        if (ft_strcmp(value, arr[1]) != 0)
        {
            printf("expand:\n\texpected: [%s]\n\tgot     : [%s]\n", arr[1], value);
            status.failure++;
        }
        else
            status.success++;
        i++;
    }
    return (status);
}

void test_export(char **env)
{
    t_status status;
    t_status tmp;

    status.failure = 0;
    status.success = 0;

    load_env(env);

    tmp = check_env(env);

    print_result(tmp);

    status.failure += tmp.failure;
    status.success += tmp.success;

    tmp = test_existing_var();

    print_result(tmp);

    status.failure += tmp.failure;
    status.success += tmp.success;

    tmp = test_non_existing_var();

    print_result(tmp);

    status.failure += tmp.failure;
    status.success += tmp.success;

    tmp = test_updating_existing_keys();

    print_result(tmp);

    status.failure += tmp.failure;
    status.success += tmp.success;

    print_total_result(status);
}