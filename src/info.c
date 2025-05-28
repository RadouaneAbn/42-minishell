#include "../include/env.h"

t_info *get_info()
{
    static t_info *info;

    if (info == NULL)
    {
        info = malloc(sizeof(t_info));
        if (info == NULL)
            return (NULL);
        ft_bzero(info, sizeof(t_info));
        info->env_size = 128;
        info->env = malloc(sizeof(char *) * info->env_size);
        if (info->env == NULL)
        {
            free(info);
            info = NULL;
            return (NULL);
        }
        ft_bzero(info->env, sizeof(char *) * info->env_size);
    }

    return (info);
}
