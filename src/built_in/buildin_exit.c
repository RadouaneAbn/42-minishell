#include <minishell.h>

long convert_exist_status(char *arg)
{
    long status;
    int tmp;
    int i;

    i = 0;
    status = 0;
    while (arg[i])
    {
        if (ft_isdigit(arg[i]) == FALSE)
            return (-1);
        tmp = arg[i] - '0';
        if (status * 10 + tmp < status)
            return (-1);
        status = status * 10 + tmp;
        i++;
    }
    return (status);
}
