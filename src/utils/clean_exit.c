#include <minishell.h>

void clean_exit(int exit_code)
{
    free_full();
    exit(exit_code);
}