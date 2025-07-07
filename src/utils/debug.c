#include <stdlib.h>
#include <stdio.h>

void print_args_list(char **args)
{
    int i;

    i = 0;
    while (args[i])
    {
        printf("%d: %s\n", i, args[i]);
        i++;
    }
}
