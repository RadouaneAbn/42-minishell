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
    printf("freed level %d\n", gc->level_n);
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



int free_elem_from_lvl(t_gc_level *level, void *data)
{
    t_gc_node *node;
    t_gc_node *tmp;

    if (!level || !data)
        return (1);
    node = level->aloc_list;
    if (node == NULL)
        return (1);
    tmp = NULL;
    if (data == node->data)
    {
        tmp = level->aloc_list;
        level->aloc_list = level->aloc_list->next;
    }
    else
    {
        while (node->next)
        {
            if (node->next->data == data)
            {
                tmp = node->next;
                node->next = node->next->next;
                break;
            }
            node = node->next;
        }
    }
    if (tmp != NULL)
    {
        printf("element freed\n");
        free(tmp->data);
        free(tmp);
        return (0);
    }
    return (1);
}

void gc_free_from_lvl(void *data)
{
    t_gc_level *level;
    t_gc_node *node;
    t_gc_node *tmp;

    level = get_current_level();
    if (level)
        free_elem(level, data);
}

void gc_free_from_lvls(void *data)
{
    t_gc_level *level;
    t_gc_node *node;
    t_gc_node *tmp;

    level = get_current_level();
    if (level == NULL)
        return ;
    while (level && free_elem(level, data) != 0)
        level = level->parent;
}
