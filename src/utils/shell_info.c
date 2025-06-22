#include <minishell.h>

t_info *get_info(void)
{
    static t_info *info;

    if (info == NULL)
    {
        info = malloc(sizeof(t_info));
        ft_bzero(info, sizeof(t_info));
    }
    return (info);
}
