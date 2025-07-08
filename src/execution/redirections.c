#include <minishell.h>

int redirect_input(char *path, t_executable_data *data)
{
    int fd;

    if (data->fd_in != -1)
        close(data->fd_in);
    fd = open(path, O_RDONLY);
    if (fd != -1)
        data->fd_in = fd;
    else
        perror(path);
    return (fd);
}

int redirect_output(char *path, t_executable_data *data)
{
    int fd;

    if (data->fd_out != -1)
        close(data->fd_out);
    fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (fd != -1)
        data->fd_out = fd;
    else
        perror(path);
    return (fd);
}

int append_output(char *path, t_executable_data *data)
{
    int fd;

    if (data->fd_out != -1)
        close(data->fd_out);
    fd = open(path, O_CREAT | O_APPEND | O_WRONLY, 0644);
    if (fd != -1)
        data->fd_out = fd;
    else
        perror(path);
    return (fd);
}

int here_doc_input(char *path, t_executable_data *data)
{
    int fd;

    if (data->fd_in != -1)
        close(data->fd_in);
    fd = open(path, O_RDONLY);
    if (fd != -1)
        data->fd_in = fd;
    else
        perror(path);
    return (fd);
}