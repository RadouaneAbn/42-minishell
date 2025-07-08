#include "../../include/garbage_colector.h"

t_gc **get_gc(void)
{
    static t_gc *gc;
    static bool init;

    if (gc == NULL && init == false)
    {
        gc = malloc(sizeof(t_gc));
        if (gc == NULL)
        {
            perror(GC_MALLOC);
            return (NULL);
        }
        gc->current_level = NULL;
        gc->level_n = 0;
        gc_level_init();
        init = true;
    }

    return (&gc);
}

t_gc_level *gc_level_init(void)
{
    t_gc_level *new_level;
    t_gc *gc;

    gc = *get_gc();
    if (gc == NULL)
        return (NULL);
    new_level = malloc(sizeof(t_gc_level));
    if (new_level == NULL)
    {
        perror(GC_MALLOC);
        return (NULL);
    }
    new_level->aloc_list = NULL;
    new_level->parent = gc->current_level;
    gc->current_level = new_level;
    gc->level_n++;
    return (gc->current_level);
}

t_gc_level *get_current_level(void)
{
    t_gc *gc;

    gc = *get_gc();
    if (gc == NULL)
        return (NULL);
    return (gc->current_level);
}

void *gc_save(void *data)
{
    t_gc_level *level;
    t_gc_node *node;
    t_gc_node *tmp;

    node = malloc(sizeof(t_gc_node));
    if (node == NULL)
    {
        perror(GC_MALLOC);
        return (NULL);
    }
    level = get_current_level();
    level = get_current_level();
    if (level == NULL)
    {
        free(node);
        return (NULL);
    }
    node->data = data;
    node->next = level->aloc_list;
    level->aloc_list = node;
    return (node);
}

void *gc_malloc(size_t size)
{
    void *data;

    data = malloc(size);
    if (data == NULL)
    {
        perror(GC_MALLOC);
        return (NULL);
    }
    if (gc_save(data) == NULL)
        return (free(data), NULL);
    return (data);
}



/* Testing */

void test_enter_level(void)
{
    gc_level_init();

    char *s = gc_malloc(10000);

    if (get_level() < 20)
        test_enter_level();
    free_level();
}

int main()
{
    char *s = gc_malloc(10000);
    strcpy(s, "entring new level");


    test_enter_level();
    // free_gc();
    // free_level();
    free_gc_full();
}