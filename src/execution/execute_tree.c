#include <minishell.h>

int get_tree_lenght(t_tree *tree)
{
    int i;

    i = 0;
    while (tree && tree->data_type == T_CMD_ARG)
    {
        i++;
        tree = tree->next;
    }
    return (i);
}

char **get_full_command_from_tree(t_tree *tree)
{
    int tree_len;
    int i;
    char **args;

    tree_len = get_tree_lenght(tree);
    args = ft_malloc(sizeof(char *) * (tree_len + 1));
    i = 0;
    while (i < tree_len)
    {
        args[i] = ft_strdup((char *)tree->data);
        tree = tree->next;
        i++;
    }
    args[i] = NULL;
    return (args);
}

void execute_command_tree(t_tree *tree)
{
    char **cmd_array;
    int status;
    pid_t pid;

    // cmd_array = get_full_command_from_tree(tree);
    cmd_array = tree_expand_simple_command(tree);
    // print_args_list(cmd_array);
    pid = -1;
    if (get_command_type((char *)tree->data) == RUN_EXECUTABLE)
        pid = fork();
    else
        execute_command_2(cmd_array, tree->sibling);
    if (pid == 0)
        execute_command(cmd_array, tree->sibling);
    if (pid != -1)
    {
        waitpid(pid, &status, 0);
        store_child_exit_status(status);
    }
}

void print_sib(t_tree *tree)
{
    char *data_type[11];
    data_type[T_COMPOUND_COMMAND] = "COMPOUND COMMAND";
    data_type[T_FILE_HERE_DOC] = "FILE_HERE_DOC";
    data_type[T_FILE_APPEND] = "FILE_APPEND";
    data_type[T_FILE_READ] = "FILE_READ";
    data_type[T_FILE_TRUNCATE] = "FILE_TRUNCATE";
    data_type[T_CMD_ARG] = "CMD ARG";
    data_type[T_AND] = "AND";
    data_type[T_OR] = "OR";
    data_type[T_COMMAND] = "COMMAND";
    data_type[T_SUBSHELL] = "SUBSHELL";
    data_type[T_PIPELINE] = "PIPELINE";

    printf("sib: [%p]\n", tree);
    if (tree)
        printf("type: [%s]\n", data_type[tree->data_type]);
    else
        printf("type: [null]\n");
}

bool sibling_is_and_or(t_tree *tree)
{
    if (tree->sibling)
    {
        if (tree->sibling->data_type == T_AND || tree->sibling->data_type == T_OR)
            return (TRUE);
    }
    return (FALSE);
}

bool is_compound_command_or_pipeline(t_tree *tree)
{
    return (tree->data_type == T_COMPOUND_COMMAND || tree->data_type == T_PIPELINE);
}

bool should_execute_next_tree(int pipe_type)
{
    int last_exit_code;

    if (pipe_type == T_COMMAND)
        return (TRUE);
    last_exit_code = get_info()->last_exit_status;
    if (pipe_type == T_AND && last_exit_code == 0)
        return (TRUE);
    if (pipe_type == T_OR && last_exit_code != 0)
        return (TRUE);
    return (FALSE);
}

bool tree_is_subshell(t_tree *tree)
{
    return (tree->next && tree->next->data_type == T_SUBSHELL);
}

bool is_piped(t_tree *tree)
{
    return (tree->data_type == T_COMMAND && tree->sibling != NULL);
}

void run_subshell(t_tree *tree)
{
    t_executable_data data;

    // print_sib(tree);
    init_executable_data(&data);
    if (handle_redirections(tree->sibling, &data) == -1)
        exit(1);
    if (data.fd_in != -1)
    {
        dup2(data.fd_in, STDIN_FILENO);
        close (data.fd_in);
    }
    if (data.fd_out != -1)
    {
        dup2(data.fd_out, STDOUT_FILENO);
        close (data.fd_out);
    }
    execute_tree(tree->next);
    exit(get_exit_status());
}

void execute_tree_subshell(t_tree *tree)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
        return ;
    if (pid == 0)
        run_subshell(tree);
    else
    {
        waitpid(pid, &status, 0);
        store_child_exit_status(status);
    }
}

void start_tree_execution(t_tree *tree)
{
    if (tree_is_subshell(tree))
    {
        execute_tree_subshell(tree->next);
    }
    else
    {
        if (is_piped(tree) == TRUE)
        {
            run_pipe_line(tree);
            return;
        }
        else
            execute_command_tree(tree->next);
    }
}

void execute_tree(t_tree *tree)
{
    int pipe_type;

    pipe_type = T_COMMAND;
    while (tree)
    {
        if (is_compound_command_or_pipeline(tree) == TRUE)
        {
            if (should_execute_next_tree(pipe_type) == TRUE)
                execute_tree(tree->next);
        }
        else if (tree->data_type == T_COMMAND)
        {
            start_tree_execution(tree);
            pipe_type = T_COMMAND;
            return;
        }
        if (sibling_is_and_or(tree) == TRUE)
        {
            pipe_type = tree->sibling->data_type;
            tree = tree->sibling;
        }
        if (tree)
            tree = tree->sibling;
    }
}
