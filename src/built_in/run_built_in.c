#include <minishell.h>

int run_export(t_executable_data *data)
{
    int status;
    char **vec;

    vec = data->lst;
    vec++;
    if (vec[0] == NULL)
        return (print_exports(data->fd_out));
    status = EXIT_SUCCESS;
    while (*vec)
    {
        status |= pre_export(*vec);
        vec++;
    }
    return (status);
}

int run_env(t_executable_data *data)
{
    char **vec;

    vec = data->lst;
    vec++;
    return (print_env(data->fd_out));
}

int run_unset(t_executable_data *data)
{
    int status;
    char **vec;

    vec = data->lst;
    vec++;
    status = EXIT_SUCCESS;
    while (*vec)
    {
        status |= unset(*vec);
        vec++;
    }
    return (status);
}

int run_echo(t_executable_data *data)
{
    char **vec;

    vec = data->lst;
    vec++;
    return (echo(vec, data->fd_out));
}

int run_pwd(t_executable_data *data)
{
    (void) data;
    char *path;

    if (data->fd_out == -1)
        data->fd_out = STDOUT_FILENO;
    path = expand_env("PWD");
    if (path[0] == '\0')
    {
        path = getcwd(NULL, 0);
        if (path == NULL)
            return (perror("minishell: pwd"), EXIT_FAILURE);
        // printf("%s\n", path);
        ft_putendl_fd(path, data->fd_out);
        free(path);
    }
    else
        ft_putendl_fd(path, data->fd_out);
    return (EXIT_SUCCESS);
}

int run_exit(t_executable_data *data)
{
    char **vec;
    char *exit_str;
    long exit_status;
    
    vec = data->lst;
    exit_str = vec[1];
    if (exit_str == NULL)
        exit_status = get_exit_status();
    else
    {
        exit_status = convert_exist_status(exit_str);
        if (exit_status == -1)
        {
            ft_putstr_fd("minishell: exit: ", 2);
            ft_putstr_fd(exit_str, 2);
            ft_putendl_fd(": numeric argument required", 2);
            exit_status = 2;
        }
    }
    exit(exit_status);
}

int command_is_empty(char *cmd)
{
    int i;

    i = 0;
    while (cmd[i])
    {
        if (cmd[i] != ' ')
            return (FALSE);
        i++;
    }
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(cmd, 2);
    ft_putendl_fd(": command not found", 2);
    return (TRUE);
}

char *get_path_from_env()
{
    char *path;

    path = expand_env("PATH");
    if (path[0] == '\0')
        return (NULL);
    return (path);
}

char *join_path(char *path, char *cmd)
{
    int t_size;
    char *str;

    t_size = ft_strlen(path) + ft_strlen(cmd) + 2;
    str = ft_malloc(t_size * sizeof(char));
    if (str == NULL)
        return (NULL);
    str[0] = 0;
    ft_strlcat(str, path, t_size);
    ft_strlcat(str, "/", t_size);
    ft_strlcat(str, cmd, t_size);
    return (str);
}

bool file_exist(char *path)
{
	if (access(path, F_OK) == 0)
		return (TRUE);
	return (FALSE);
}

char *find_file(char *cmd)
{
    char **path;
    char *path_env;
    char *cmd_abs_path;
    int i;

    path_env = get_path_from_env();
    if (path_env == NULL)
        return (cmd);
    path = ft_split(path_env, ':');
    i = 0;
    while (path[i])
    {
        cmd_abs_path = join_path(path[i], cmd);
        if (file_exist(cmd_abs_path) == TRUE)
            return (free(cmd), cmd_abs_path);
        free(cmd_abs_path);
        i++;
    }
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(cmd, 2);
    ft_putendl_fd(": command not found", 2);
    exit(127);
}

char *node_to_string(t_node *node)
{
    char *s;
    int t_size;

    t_size = ft_strlen(node->key) + ft_strlen(node->value) + 2;
    s = ft_malloc(t_size * sizeof(char));
    s[0] = 0;
    ft_strlcat(s, node->key, t_size);
    ft_strlcat(s, "=", t_size);
    ft_strlcat(s, node->value, t_size);
    return (s);
}

char **build_env(void)
{
    t_map *map;
    char **env;
    t_node *node;
    int i;

    map = get_map();
    node = map->ordered_list;
    env = ft_malloc((map->size + 1) * sizeof(char *));
    i = 0;
    while (node)
    {
        if (node->value)
            env[i++] = node_to_string(node);
        node = node->ordered_next;
    }
    env[i] = NULL;
    return (env);
}

void print_error(char *m1, char *m2, char *m3, char *message)
{
    ft_putstr_fd("minishell: ", 2);
    if (m1)
    {
        ft_putstr_fd(m1, 2);
        ft_putstr_fd(": ", 2);
    }
    if (m2)
    {
        ft_putstr_fd(m2, 2);
        ft_putstr_fd(": ", 2);
    }
    if (m3)
    {
        ft_putstr_fd(m3, 2);
        ft_putstr_fd(": ", 2);
    }
    ft_putendl_fd(message, 2);
}

bool has_exec_perm(char *path)
{
    return (access(path, X_OK) == 0);
}

int execute_command_exec(t_executable_data *data)
{
    char **vec;

    vec = data->lst;
    if (has_exec_perm(data->lst[0]) == false)
    {
        print_error(data->lst[0], NULL, NULL, "Permission denied");
        exit(126);
    }
    if (is_dir(data->lst[0]) == true)
    {
        print_error(data->lst[0], NULL, NULL, "Is a directory");
        exit(126);
    }
    if (execve(vec[0], vec, build_env()) == -1)
    {
        perror("minishell: execve");
        exit(1);
    }
    return (TRUE);
}

int run_executable(t_executable_data *data)
{
    char **vec;

    vec = data->lst;
    if (vec[0] == NULL)
        exit(0);
    if (command_is_empty(vec[0]))
        exit(127);
    if (ft_strchr(vec[0], '/') == NULL)
        vec[0] = find_file(vec[0]);
    if (data->fd_in != -1)
        dup2(data->fd_in, STDIN_FILENO);
    if (data->fd_out != -1)
        dup2(data->fd_out, STDOUT_FILENO);
    return (execute_command_exec(data));
}