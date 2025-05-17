
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "libft/libft.h"

#define MAP_SIZE 1000

typedef struct s_node t_node;

struct s_node
{
	char *key;
	char *value;
	t_node *next;
	t_node *ordered_next;
};

struct s_env
{
	char **env;
	t_map exports;
	char **path;
	int last_exit_status;
	int env_size;
};


typedef struct s_map
{
	t_node *map[MAP_SIZE];
	t_node *ordered_list;
}	t_map;

int index_key(char *key)
{
	int i;
	int key_index;

	i = 0;
	key_index = 0;
	while (key[i])
	{
		key_index = (key_index + (int) key[i]) % MAP_SIZE;
		i++;
	}
	return (key_index);
}

t_node *create_new_node(char *key, char *value)
{
	t_node *node;

	node = malloc(sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->key = strdup(key);
	node->value = strdup(value);
	node->next = NULL;
	node->ordered_next = NULL;
	return (node);
}

t_node *find_in_map(t_map *map, char *key)
{
	int idx;
	t_node *curr;

	idx = index_key(key);
	curr = map->map[idx];
	while (curr)
	{
		if (strcmp(curr->key, key) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

// TODO: Find a better way to implement this function
void append_to_ordered_list(t_map *map, t_node *node)
{
	t_node *curr;
	t_node *prev;

	curr = map->ordered_list;
	prev = NULL;
	while (curr && strcmp(curr->key, node->key) < 0)
	{
		prev = curr;
		curr = curr->ordered_next;
	}
	if (curr == map->ordered_list)
	{
		node->ordered_next = map->ordered_list;
		map->ordered_list = node;
	}
	else
	{
		if (curr != NULL)
			node->ordered_next = curr;
		prev->ordered_next = node;
	}
}
	
void add_to_map(t_map *map, char *key, char *value)
{
	int idx;
	t_node *node;

	if (!key || !value) // TODO: Check if the key or value are not empty (compaire to bash)
		return ;

	node = find_in_map(map, key);
	if (node == NULL)
	{
		idx = index_key(key);
		node = create_new_node(key, value);
		if (node == NULL)
			return ;
		node->next = map->map[idx];
		map->map[idx] = node;
		append_to_ordered_list(map, node);
	}
	else
	{
		free(node->value);
		node->value = strdup(value);
	}
}

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

int main()
{
	t_map map;
	bzero(&map, sizeof(map));
	char buf[1000];
	ssize_t size;
	int i = 0;
	t_node *node;
	char *arr[][2] = {
		{"var", "13"},
		{"NAME", "Radouane"},
		{"HOME", "/home/red"},
		{"EXP", "1337"},
		{"SCHOOL", "42 Network"},
		{"age", "27"},
		{NULL, NULL}
	};

	char **exp;
	while (1)
	{
		write(1, "-> ", 3);
		size = read(0, buf, 100);
		if (size <= 0)
			break;
		buf[size - 1] = 0;
		exp = ft_split(buf, ' ');
		if (exp[0] == NULL)
			continue ;
		// for (int k = 0; exp[k]; k++)
		// 	printf("exp[%d]: \"%s\"\n", k, exp[k]);
		if (strcmp(exp[0], "set") == 0)
			add_to_map(&map, exp[1], exp[2]);
		else if (strcmp(exp[0], "get") == 0)
		{
			node = find_in_map(&map, exp[1]);
			if (node)
				printf("arr[%s]: %s\n", node->key, node->value);
			else
				printf("arr[%s]: %s\n", exp[1], "(null)");
		}
		else if (strcmp(exp[0], "all") == 0)
		{
			print_all_ordered(&map);
		}
		else if (strcmp(exp[0], "exit") == 0)
			break;
		else
			printf("command not found !!!\n");
	}



	/*
	while (arr[i][0])
	{
		add_to_map(&map, arr[i][0], arr[i][1]);
		i++;
	}

	i = 0;
	char bs = 8;
	printf("MAP Contains:\n");
	while (1) {
		write(1, "\narr[", 5);
		size = read(0, buf, 100);
		if (size <= 0)
			break;
		buf[size - 1] = 0;
		node = find_in_map(&map, buf);
		printf("\033[Aarr[%s] = %s\n", node->key, node->value);
	}
	*/

	
}
