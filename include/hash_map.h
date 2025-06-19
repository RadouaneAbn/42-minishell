#ifndef HASH_MAP_H
#define HASH_MAP_H

#define MAP_SIZE 1000
#define TRUE 1
#define FALSE 0

typedef struct s_node t_node;

struct s_node
{
	char *key;
	char *value;
	t_node *next;
	t_node *ordered_next;
};

typedef struct s_map
{
	t_node *map[MAP_SIZE];
	t_node *ordered_list;
}	t_map;


int index_key(char *key);
t_node *create_new_node(char *key, char *value);
t_node *find_in_map(t_map *map, char *key);
void append_to_ordered_list(t_map *map, t_node *node);
void add_to_map(t_map *map, char *key, char *value);
void remove_from_map(t_map *map, char *key);
void remove_from_ordered_list(t_map *map, char *key);

#endif