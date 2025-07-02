#include <minishell.h>

void handle_pipe(t_executable_data *data, int fd_in, int fd_out)
{
    (void) data;
    if (fd_in != -1)
    {
        if (dup2(fd_in, STDIN_FILENO) == -1)
        {
            perror("dup2 stdin");
            exit(1);
        }
        close(fd_in);
    }
    
    // Set up stdout to pipe
    if (fd_out != -1)
    {
        if (dup2(fd_out, STDOUT_FILENO) == -1)
        {
            perror("dup2 stdout");
            exit(1);
        }
        close(fd_out);
    }
}

void execute_command_piped(char **cmdv, t_tree *tree, int fd_in, int fd_out)
{
    t_cmd_type cmd_type;
    t_func_ptr *exec_functions;
    t_executable_data data;
    int status;

    cmd_type = get_command_type(cmdv[0]);
    exec_functions = get_exec_functions();
    init_executable_data(&data);
    handle_pipe(&data, fd_in, fd_out);
    if (handle_redirections(tree, &data) == -1)
        exit (1);
    data.lst = cmdv;
    data.fds = tree;
    status = exec_functions[cmd_type](&data);
    exit(status);
}

pid_t execute_command_tree_piped(t_tree *tree, int fd_in, int fd_out)
{
    char **cmd_array;
    pid_t pid;

    cmd_array = get_full_command_from_tree(tree);
    pid = fork();
    if (pid == 0)
        execute_command_piped(cmd_array, tree->sibling, fd_in, fd_out);
    return (pid);
}

void wait_for_children(pid_t last_pid)
{
    int status;
    pid_t wpid;

    // errno = 0;
    while ((wpid = waitpid(-1, &status, 0)) > 0)         
    {
        if (wpid == last_pid) {                        
            if (WIFEXITED(status))
                set_exit_status(WEXITSTATUS(status));
            else if (WIFSIGNALED(status))
                set_exit_status(128 + WTERMSIG(status));   
            else
                set_exit_status(1);
        }
    }
}

void run_pipe_line(t_tree *tree)
{
    int prev_fd;
    int fd[2];
    int (fd_in), (fd_out);
    pid_t last_pid;

    prev_fd = -1;
    while (tree)
    {
        if (tree->sibling)
        {
            if (pipe(fd) == -1)
            {
                perror("minishell: pipe"); // set exit code after
                return ;
            }
        }
        fd_in = -1;
        fd_out = -1;
        if (prev_fd != -1)
            fd_in = prev_fd;
        if (tree->sibling)
            fd_out = fd[1];
        last_pid = execute_command_tree_piped(tree->next, fd_in, fd_out);
        if (fd_in != -1)
            close(fd_in);
        if (fd_out != -1)
            close(fd_out);
        if (tree->sibling)
            prev_fd = fd[0];
        tree = tree->sibling;
    }

    wait_for_children(last_pid);
}
