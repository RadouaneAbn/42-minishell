#include <minishell.h>

static bool var_found(char *var)
{
    return (var[0] != '\0');
}

static int chdir_home(void)
{
    char *path;

    path = expand_env("HOME");
    if (var_found(path) == FALSE)
        return (print_cmd_error("cd: HOME not set\n"));
    if (chdir(path) != 0)
    {
        perror("minishell: cd");
        return (EXIT_FAILURE);
    }
    export("OLDPWD", ft_strdup(expand_env("PWD")));
    export("PWD", ft_strdup(path));
    return (EXIT_SUCCESS);
}

static int chdir_oldpwd(void)
{
    char *path;

    path = expand_env("OLDPWD");
    if (var_found(path) == FALSE)
        return (print_cmd_error("cd: OLDPWD not set\n"));
    if (chdir(path) != 0)
    {
        perror("minishell: cd");
        return (EXIT_FAILURE);
    }
    export("OLDPWD", ft_strdup(expand_env("PWD")));
    export("PWD", ft_strdup(path));
    return (EXIT_SUCCESS);
}

/*
    hello/worl
    0123456789
    j....i....
*/

char *get_parent_path(char *path)
{
    int i;
    int j;
    char *parent;

    i = ft_strlen(path) - 1;
    while (path[i] != '/')
        i--;
    j = 0;
    if (i == 0)
        return (ft_strdup(path));
    parent = ft_malloc((i + 1) * sizeof(char));
    while (j < i)
    {
        parent[j] = path[j];
        j++;
    }
    parent[j] = 0;
    return (parent);
}

/**
 * hel///wo//
 * 0123456789
 * ......jjji
 */

char *simplify_path(char *path)
{
    int j;
    int i;
    char *simple_path;

    i = 0;
    j = 0;
    while (path[i])
    {
        j = i;
        while (path[j] && path[j] != '/')
            j++;
        i = j;
        while (path[i] && path[i] == '/')
            i++;
    }
    simple_path = ft_malloc(j + 1);
    i = 0;
    j = 0;
    while (path[i])
    {
        j = i;
        while (path[i] && path[i] != '/')
            simple_path[j++] = path[i++];
        simple_path[j++] = '/';
        while (path[i] && path[i] == '/')
            i++;
    }
    simple_path[j] = 0;
    return (simple_path);
}

char *join_path_cd(char *pwd, char *path)
{
    int size;
    char *new_path;

    size = ft_strlen(pwd) + ft_strlen(path) + 2;
    new_path = ft_malloc(size);
    new_path[0] = 0;
    ft_strlcat(new_path, pwd, size);
    ft_strlcat(new_path, "/", size);
    ft_strlcat(new_path, path, size);
    return (new_path);
}

char *clean_path(char *pwd, char *path)
{
    char *simple_path;

    simple_path = simplify_path(path);
    if (ft_strcmp(simple_path, ".") == 0)
        return (ft_strdup(pwd));
    if (ft_strcmp(simple_path, "..") == 0)
        return (get_parent_path(simple_path));
    if (simple_path[0] == '/')
        return (ft_strdup(simple_path));
    return (join_path_cd(pwd, simple_path));
}

int chdir_path(char *path)
{
    char *cleaned_path;
    char *pwd;

    if (chdir(path) != 0)
    {  
        perror("minishell: cd");
        return (EXIT_FAILURE);
    }
    pwd = expand_env("PWD");
    export("OLDPWD", ft_strdup(pwd));
    cleaned_path = clean_path(pwd, path);
    export("PWD", cleaned_path);
    return (EXIT_SUCCESS);
}

int run_cd(t_executable_data *data)
{
    char **vec;
    int status;

    vec = data->lst;
    if (vec[1] != NULL && vec[2] != NULL)
        return (print_cmd_error("cd: too many arguments"));
    if (vec[1] == NULL)
        status = chdir_home();
    else if (ft_strcmp(vec[1], "-") == 0)
        status = chdir_oldpwd();
    else
        status = chdir_path(vec[1]);
    return (status);
}
