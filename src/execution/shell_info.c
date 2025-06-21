#include <minishell.h>

t_shell *get_info()
{
    static t_shell *info;

    if (info == NULL)
    {
        info = malloc(sizeof(t_info));
        ft_bzero(info, sizeof(t_info));
    }
    return (info);
}
