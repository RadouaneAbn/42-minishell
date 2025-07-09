#include "../../include/garbage_colector.h"

int gc_status(void)
{
    t_gc * gc = *get_gc();

    printf("current level %d\n", gc->level_n);
    return (gc->level_n);
}

int get_level(void)
{
    t_gc **gc_ptr = get_gc();
    if (!gc_ptr || !*gc_ptr)
        return (-1);
    return ((*gc_ptr)->level_n);
}