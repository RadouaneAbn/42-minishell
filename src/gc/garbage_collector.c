#include "../../include/garbage_colector.h"

void *ft_malloc(size_t size)
{
    static int i;

    if (i++ < 500)
        return (malloc(size));
    printf("malloc failed\n");
    return (NULL);
}

t_gc **get_gc(void)
{
    static t_gc *gc;
    static bool init;

    if (gc == NULL && init == false)
    {
        gc = ft_malloc(sizeof(t_gc));
        if (gc == NULL)
        {
            perror(GC_MALLOC);
            exit(1);
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
    new_level = ft_malloc(sizeof(t_gc_level));
    if (new_level == NULL)
    {
        free_gc_full();
        perror(GC_MALLOC);
        exit(1);
    }
    new_level->aloc_list = NULL;
    new_level->parent = gc->current_level;
    gc->current_level = new_level;
    printf("new level %d\n", gc->level_n);
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

    node = ft_malloc(sizeof(t_gc_node));
    if (node == NULL)
    {
        free_gc_full();
        perror(GC_MALLOC);
        exit(1);
    }
    level = get_current_level();
    if (level == NULL)
    {
        free(node);
        free_gc_full();
        exit(1);
    }
    node->data = data;
    node->next = level->aloc_list;
    level->aloc_list = node;
    return (node);
}

void *gc_malloc(size_t size)
{
    void *data;

    data = ft_malloc(size);
    if (data == NULL)
    {
        perror(GC_MALLOC);
        free_gc_full();
        exit(1);
    }
    if (gc_save(data) == NULL)
    {
        free(data);
        free_gc_full();
        exit (1);
    }
    return (data);
}

/* Testing */

void test_enter_level(void)
{
    gc_level_init();

    char *s = gc_malloc(10000);
    // if (s == NULL)
    // {
    //     free_level();
    //     return (NULL);
    // }

    if (get_level() < 5)
        test_enter_level();
    free_level();
}

int main()
{
    char *s = gc_malloc(10000);
    strcpy(s, "entring new level");


    free_lvl_elm(s);
    test_enter_level();
    free_level();
    free_gc();
    // free_gc_full();
}