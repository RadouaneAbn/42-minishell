#include "../../include/garbage_colector.h"

void level_down(void)
{
    t_gc *gc;

    gc = *get_gc();
    if (!gc || !gc->current_level)
        return;
    gc->current_level = gc->current_level->parent;
    gc->level_n--;
}

void free_level(void)
{
    t_gc *gc;
    t_gc_level *current_level;
    t_gc_node *node;
    t_gc_node *tmp;

    gc = *get_gc();
    if (!gc || !gc->current_level)
        return ;
    current_level = get_current_level();
    node = current_level->aloc_list;
    while (node)
    {
        tmp = node;
        node = node->next;
        free(tmp->data);
        free(tmp);
    };
    // printf("freed level %d\n", gc->level_n);
    level_down();
    free(current_level);
}

void free_gc(void)
{
    t_gc **gc;

    gc = get_gc();
    if (*gc == NULL || (*gc)->current_level != NULL)
        return ;
    free(*gc);
    *gc = NULL;
}

void free_gc_full(void)
{
    t_gc *gc;
    t_gc_level *level;
    t_gc_node *node;

    gc = *get_gc();
    if (gc == NULL)
        return ;
    while (gc->current_level)
        free_level();
    free_gc();
}