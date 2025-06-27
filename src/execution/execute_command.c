#include <minishell.h>

t_cmd_type get_command_type (char *cmd)
{
    char *built_ins[] = {
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
        return (FALSE);
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

int execute_command(char **cmdv)
{
    t_cmd_type cmd_type;
    t_func_ptr *exec_functions;

    cmd_type = get_command_type(cmdv[0]);
    exec_functions = get_exec_functions();
    return (exec_functions[cmd_type](cmdv));
}
