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

void print_error(char *cmd, char *file, char *msg1, char *error_msg)
{
    ft_putstr_fd("minishell: ", 2);
    if (cmd)
    {
        ft_putstr_fd(cmd, 2);
        ft_putstr_fd(": ", 2);
    }
    if (file)
    {
        ft_putstr_fd(file, 2);
        ft_putstr_fd(": ", 2);
    }
    if (msg1)
    {
        ft_putstr_fd(msg1, 2);
        ft_putstr_fd(": ", 2);
    }
    ft_putendl_fd(error_msg, 2);
}
