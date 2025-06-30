#include <minishell.h>

int print_cmd_error(char *error)
{
    int size;
    char *error_msg;

    size = ft_strlen(error) + 12;
    error_msg = ft_malloc(size);
    error_msg[0] = 0;
    ft_strlcat(error_msg, "minishell: ", size);
    ft_strlcat(error_msg, error, size);
    write(2, error_msg, size);
    return (EXIT_FAILURE);
}
