#include "../../include/libft.h"
#include "../../include/hash_map.h"
#include "../../include/utils.h"

#define NO_FLAG 0
#define NO_NL 1

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

int echo(char **vec)
{
    int i;
    int start;
    int flag;
    int t_flag;

    i = 0;
    start = 0;
    flag = NO_FLAG;
    t_flag = NO_FLAG;
    while (vec[i] != NULL)
    {
        flag = check_flag(vec[i]);
        if (flag == NO_NL)
            start = i + 1;
        else
            break;
        t_flag |= flag;
        i++;
    }
    while (vec[start])
    {
        write(1, vec[start], ft_strlen(vec[start]));
        if (vec[start + 1] != NULL)
            write(1, " ", 1);
        start++;
    }
    if (t_flag != NO_NL)
        write(1, "\n", 1);
    return (0);
}
