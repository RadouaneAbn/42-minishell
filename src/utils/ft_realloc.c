#include "../../include/libft.h"

void *ft_realloc(void *data, size_t old_size, size_t size)
{
    void *new_data;

    new_data = malloc(size);
    if (new_data == NULL)
        return (NULL);
    ft_bzero(new_data, size);
    if (data != NULL)
        ft_memcpy(new_data, data, old_size); 
    free(data);
    return (new_data);
}