#include <minishell.h>

int get_exit_status(void)
{
    return (get_info()->last_exit_status);
}

void set_exit_status(int status)
{
    t_info *info;

    info = get_info();
    info->last_exit_status = status;
}

void store_child_exit_status(int status)
{
    if (WIFEXITED(status))
        set_exit_status(WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        set_exit_status(128 + WTERMSIG(status));
    else
        set_exit_status(EXIT_FAILURE);
}