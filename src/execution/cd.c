#include <minishell.h>

int cd(char *path)
{
    if (path == NULL)
          return (1);
    chdir(path);
}