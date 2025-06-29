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
    printf("%s\n", expand_env("PWD"));
    return (EXIT_SUCCESS);
}

int run_cd(t_executable_data *data)
{
    char **vec;

    vec = data->lst;
    vec++;
    printf("running cd\n");
    return (EXIT_SUCCESS);
}

int run_exit(t_executable_data *data)
{
    char **vec;

    vec = data->lst;
    vec++;
    exit(42);
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
    ft_putendl_fd(CMD_NOT_FOUND, 2);
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
    ft_putendl_fd(CMD_NOT_FOUND, 2);
    exit(127);
    return (NULL);
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

int execute_command_exec(t_executable_data *data)
{
    char **vec;

    vec = data->lst;
    // print_args_list(build_env());
    if (execve(vec[0], vec, build_env()) == -1)
    {
        perror("execve");
        exit(1);
    }
    return (TRUE);
}

int run_executable(t_executable_data *data)
{
    char **vec;

    vec = data->lst;
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