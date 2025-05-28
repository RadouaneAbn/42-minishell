#include "tests.h"

void print_all_ordered(t_map *map)
{
	t_node *curr;

	curr = map->ordered_list;
	while (curr)
	{
		printf("%s=%s\n", curr->key, curr->value);
		curr = curr->ordered_next;
	}
}

void free_array(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
        free(arr[i++]);
    free(arr);
}

void hash_map_tests(char **env)
{
	t_map map;
    int success;
    int total_success;
    int fail;
    int total_fail;
    int map_size;
	ft_bzero(&map, sizeof(map));
	int i = 0;
	t_node *node;
    char **splited;
	char *arr[][2] = {
		{"var", "13"},
		{"NAME", "Radouane"},
		{"HOME", "/home/red"},
		{"EXP", "1337"},
		{"SCHOOL", "42 Network"},
		{"age", "27"},
		{NULL}
	};
    char *non_existing_keys[] = {
        "fpwofjoe",
        "ogiurguergb",
        "eoiqiegnirengoig",
        "efwejpewjhirg",
        "oiewhncyqwrqfenflk",
        "wefefwfklnenfpiefn",
        "felknpefiwfnpoefp",
        "ewopfjefpwenfponpef",
        "19988565151516",
        "156we1f65",
        NULL
    };

    if (env[0] == NULL)
    {
        printf("env is empty\n");
        return ;
    }
    map_size = 0;
    printf("%s#####################################\n", CYAN);
    printf(">  Running tests for the hash map:  <\n");
    printf("#####################################%s\n\n", RESET);
    
    printf("%sAdding env to the hash map...%s\n\n", BROWN, RESET);
    
	i = 0;
    while (env[i])
    {
        if (env[i][0] != '_')
        {
            splited = ft_split(env[i], '=');
            add_to_map(&map, splited[0], splited[1]);
            free_array(splited);
            map_size++;
        }
        i++;
    }
    
    printf("%sChecking if the env variables exist in the map:%s\n", PURPLE, RESET);
    i = 0;
    success = 0;
    fail = 0;
    total_success = 0;
    total_fail = 0;
	while (env[i])
    {
        if (env[i][0] != '_')
        {
            splited = ft_split(env[i], '=');
            node = find_in_map(&map, splited[0]);
            if (node == NULL ||
                (splited[1] && strcmp(node->value, splited[1])) ||
                (splited[1] == NULL && node->value != NULL))
                fail++;
            else
                success++;
        }
        i++;
    }
    printf("%sSuccess: %d\n%sFailes:  %d%s\n", GREEN, success, RED, fail, RESET);
        
    printf("\n%sChecking newly added key value pairs:%s\n", PURPLE, RESET);
    i = 0;
    while (arr[i][0])
    {
        add_to_map(&map, arr[i][0], arr[i][1]);
        map_size++;
        i++;
    }

    total_success += success;
    total_fail += fail;
    i = 0;
    success = 0;
    fail = 0;
    while (arr[i][0])
    {
        node = find_in_map(&map, arr[i][0]);
        if (node == NULL || strcmp(node->value, arr[i][1]))
            fail++;
        else
            success++;
        i++;
    }
    printf("%sSuccess: %d\n%sFailes:  %d%s\n", GREEN, success, RED, fail, RESET);
    
    printf("\n%sChecking non existing keys:%s\n", PURPLE, RESET);
    total_success += success;
    total_fail += fail;
    i = 0;
    success = 0;
    fail = 0;
    while (i < 11)
    {
        node = find_in_map(&map, non_existing_keys[i]);
        if (node != NULL)
            fail++;
        else
            success++;
        i++;
    }
    printf("%sSuccess: %d\n%sFailes:  %d%s\n", GREEN, success, RED, fail, RESET);

    printf("\n%sChecking is the added key are ordered:%s\n", PURPLE, RESET);
    node = map.ordered_list;
    total_success += success;
    total_fail += fail;
    i = 0;
    success = 0;
    fail = 0;
    while (i < map_size)
    {
        if (node)
        {
            if (node->ordered_next && strcmp(node->key, node->ordered_next->key) > 0)
                fail++;
            else
                success++;
        }
        else
            fail++;
        i++;
    }
    total_success += success;
    total_fail += fail;
    printf("%sSuccess: %d\n%sFailes:  %d%s\n", GREEN, success, RED, fail, RESET);

    printf("\n%sTests result:%s\n", CYAN, RESET);
    printf("%sTotal success: %d\n%sTotal failes:  %d%s\n", GREEN, total_success, RED, total_fail, RESET);

}
