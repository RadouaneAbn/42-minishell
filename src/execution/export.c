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

    args = split_export_args(exported);
    if (key_isvalid(args[0]) == FALSE)
        return (1);
    export(args[0], args[1]);
    free(args[0]);
    free(args[1]);
    free(args);
    return (0);
}

void export(char *key, char *value)
{
    t_map *map;

    map = get_map();
    if (map == NULL)
        return ;
    add_to_map(map, key, value);
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
