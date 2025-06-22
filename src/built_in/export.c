#include <minishell.h>

t_map *get_map()
{
    t_info *info;

    info = get_info();
    if (info == NULL)
        return (NULL);
    return (&(info->exports));
}

char **split_export_args(char *arg)
{
    int idx;
    char **arr;

    if (arg == NULL)
        return (NULL);
    arr = malloc(sizeof(char *) * 3);
    if (arr == NULL)
        return (NULL);
    idx = ft_index_of(arg, '=');
    if (idx != -1)
    {
        arr[0] = ft_substr(arg, 0, idx);
        arr[1] = ft_substr(arg, idx + 1, ft_strlen(arg) - idx);
        arr[2] = NULL;
    }
    else
    {
        arr[0] = ft_strdup(arg);
        arr[1] = NULL;
        arr[2] = NULL;
    }
    return (arr);
}

int key_isvalid(char *key)
{
    if (ft_isalpha(key[0]) || key[0] == '_')
        return (TRUE);
    return (FALSE);
}

int pre_export(char *exported)
{
    char **args;
    int status;

    args = split_export_args(exported);
    if (key_isvalid(args[0]) == FALSE)
        return (1);
    status = export(args[0], args[1]);
    free(args[0]);
    free(args[1]);
    free(args);
    return (status);
}

int export(char *key, char *value)
{
    t_map *map;

    map = get_map();
    if (map == NULL)
        return (1);
    return (add_to_map(map, key, value));
}
