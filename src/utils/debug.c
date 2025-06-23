#include <stdlib.h>
#include <stdio.h>

void print_args_list(char **args)
{
    int i;

    i = 0;
    printf("{");
    while (args[i])
    {
        printf("\"%s\"", args[i]);
        if (args[i + 1] != NULL)
            printf(", ");
        i++;
    }
    printf("}\n");
}
