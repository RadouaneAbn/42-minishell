#include <minishell.h>

int check_flag(char *str)
{
    int i;
    int flag;

    if (str[0] != '-')
        return (NO_FLAG);
    flag = NO_FLAG;
    i = 1;
    while (str[i])
    {
        if (str[i] == 'n')
            flag = NO_NL;
        else
            return (NO_FLAG);
        i++;
    }
    return (flag);
}

int get_flag(char **vec, int *start)
{
    int flag;
    int t_flag;
    int i;

    i = 0;
    flag = NO_FLAG;
    t_flag = NO_FLAG;
    while (vec[i] != NULL)
    {
        flag = check_flag(vec[i]);
        if (flag == NO_NL)
            *start = i + 1;
        else
            break;
        t_flag |= flag;
        i++;
    }
    return (t_flag);
}

int echo(char **vec, int fd)
{
    int start;
    int t_flag;

    start = 0;
    t_flag = get_flag(vec, &start);
    if (fd == -1)
        fd = 1;
    while (vec[start])
    {
        write(fd, vec[start], ft_strlen(vec[start]));
        if (vec[start + 1] != NULL)
            write(fd, " ", 1);
        start++;
    }
    if (t_flag != NO_NL)
        write(fd, "\n", 1);
    return (0);
}
