
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../include/libft.h"
#include "../include/hash_map.h"

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
	node->key = ft_strdup(key);
	if (node->key != NULL)
	{
		node->value = ft_strdup(value);
		if (value != NULL && node->value == NULL)
			free (node->key);
		else
		{
			node->next = NULL;
			node->ordered_next = NULL;
			return (node);
		}
	}
	free (node);
	return (NULL);
}

t_node *find_in_map(t_map *map, char *key)
{
	int idx;
	t_node *curr;

	if (key == NULL)
		return (NULL);
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

	if (!key)
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
	else if (value != NULL)
	{
		/* If the key already exists it wont the change the value if its NULL */
		free(node->value);
		node->value = ft_strdup(value);
	}
}
