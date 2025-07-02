#include <minishell.h>

int run_cd(t_executable_data *data)
{
    char **vec;
    char *new_path;
    char *path;

    vec = data->lst;
    if (vec[1] != NULL && vec[2] != NULL)
        return (print_cmd_error("cd: too many arguments"));
    if (vec[1])
        path = vec[1];
    else if (vec[1] == NULL)
    {
        path = expand_env("HOME");
        if (path == NULL)
            return (print_cmd_error("cd: HOME not set"));
    }
    if (chdir(path) != 0)
        return (perror("minishell: cd"), EXIT_FAILURE);
    new_path = getcwd(NULL, 0);
    export("OLDPWD", expand_env("PWD"));
    export("PWD", new_path);
    free(new_path);
    return (EXIT_SUCCESS);
}
