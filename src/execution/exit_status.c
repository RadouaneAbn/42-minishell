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
