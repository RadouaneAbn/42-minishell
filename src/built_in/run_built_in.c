#include <minishell.h>

int run_export(char **vec)
{
    int status;

    vec++;
    if (vec[0] == NULL)
        return (print_exports());
    status = EXIT_SUCCESS;
    while (*vec)
    {
        status |= pre_export(*vec);
        vec++;
    }
    return (status);
}

int run_env(char **vec)
{
    vec++;
    return (print_env());
}

int run_unset(char **vec)
{
    int status;

    vec++;
    status = EXIT_SUCCESS;
    while (*vec)
    {
        status |= unset(*vec);
        vec++;
    }
    return (status);
}

int run_echo(char **vec)
{
    vec++;
    return (echo(vec));
}

int run_pwd(char **vec)
{
    vec++;
    printf("%s\n", expand_env("PWD"));
    return (EXIT_SUCCESS);
}

int run_cd(char **vec)
{
    vec++;
    printf("running cd\n");
    return (EXIT_SUCCESS);
}

int run_exit(char **vec)
{
    vec++;
    printf("running exit\n");
    return (EXIT_SUCCESS);
}

int run_executable(char **vec)
{
    printf("running %s\n", vec[0]);
    return (EXIT_SUCCESS);
}