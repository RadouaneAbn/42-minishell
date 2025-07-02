#include <minishell.h>

t_cmd_type get_command_type (char *cmd)
{
    static char *built_ins[8] = {
        "export",
        "env",
        "unset",
        "echo",
        "pwd",
        "cd",
        "exit",
        NULL
    };
    int i;

    if (cmd == NULL)
        return (RUN_EXECUTABLE);
    i = RUN_EXPORT;
    while (built_ins[i])
    {
        if (ft_strcmp(built_ins[i], cmd) == 0)
            break;
        i++;
    }
    return (i);
}

t_func_ptr *get_exec_functions(void)
{
    static t_func_ptr exec_functions[8] = {
        run_export,
        run_env,
        run_unset,
        run_echo,
        run_pwd,
        run_cd,
        run_exit,
        run_executable
    };
    return (exec_functions);
}

int handle_redirections(t_tree *tree, t_executable_data *data)
{
    int status;

    while (tree)
    {
        if (tree->data_type == RED_IN)
            status = redirect_input((char *)tree->data, data);
        else if (tree->data_type == RED_OUT)
            status = redirect_output((char *)tree->data, data);
        else if (tree->data_type == APPEND_OUT)
            status = append_output((char *)tree->data, data);
        else if (tree->data_type == HERE_DOC)
            status = here_doc_input((char *)tree->data, data);
        if (status == -1)
            return (-1);
        tree = tree->next;
    }
    return (0);
}

void init_executable_data(t_executable_data *data)
{
    data->fd_in = -1;
    data->fd_out = -1;
    data->fds = NULL;
    data->lst = NULL;
}

void execute_command(char **cmdv, t_tree *tree)
{
    t_cmd_type cmd_type;
    t_func_ptr *exec_functions;
    t_executable_data data;
    int status;

    cmd_type = get_command_type(cmdv[0]);
    exec_functions = get_exec_functions();
    init_executable_data(&data);
    if (handle_redirections(tree, &data) == -1)
        exit (1);
    data.lst = cmdv;
    data.fds = tree;
    status = exec_functions[cmd_type](&data);
    exit(status);
}

void execute_command_2(char **cmdv, t_tree *tree)
{
    t_cmd_type cmd_type;
    t_func_ptr *exec_functions;
    t_executable_data data;
    int status;

    cmd_type = get_command_type(cmdv[0]);
    exec_functions = get_exec_functions();
    init_executable_data(&data);
    if (handle_redirections(tree, &data) == -1)
    {
        set_exit_status(2);
        return ;
    }
    data.lst = cmdv;
    data.fds = tree;
    status = exec_functions[cmd_type](&data);
    set_exit_status(status);
}
