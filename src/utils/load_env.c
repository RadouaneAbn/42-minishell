#include <minishell.h>

void load_env(char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        pre_export(env[i]);
        i++;
    }
}