#ifndef GARBAG_H
#define GARBAG_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

# define GC_MALLOC "minishell: garbage collector"

typedef struct s_gc_node
{
    void *data;
    struct s_gc_node *next;
} t_gc_node;

typedef struct s_gc_level
{
    t_gc_node *aloc_list;
    struct s_gc_level *parent;
} t_gc_level;

typedef struct s_gc
{
    t_gc_level *current_level;
    int level_n;
} t_gc;

t_gc **get_gc(void);
t_gc_level *gc_level_init(void);
t_gc_level *get_current_level(void);
void *gc_save(void *data);
void *gc_malloc(size_t size);
void level_down(void);
void free_level(void);
void free_gc(void);
void free_gc_full(void);
void free_lvl_elm(void *data);
void free_all_elm(void *data);


/* Debug */

int gc_status(void);
int get_level(void);


#endif