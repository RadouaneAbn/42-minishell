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
    i = 0;
    while (built_ins[i])
    {
        if (ft_strcmp(built_ins[i], cmd) == 0)
            break;
        i++;
    }
    return (i);
}

t_func *get_exec_functions(void)
{
    static t_func exec_functions[8] = {
        {.type = RUN_EXPORT, .f = run_export},
        {.type = RUN_ENV, .f = run_env},
        {.type = RUN_UNSET, .f = run_unset},
        {.type = RUN_ECHO, .f = run_echo},
        {.type = RUN_PWD, .f = run_pwd},
        {.type = RUN_CD, .f = run_cd},
        {.type = RUN_EXIT, .f = run_exit},
        {.type = RUN_EXECUTABLE, .f = run_executable}
    };
    return (exec_functions);
}

int execute_command(char **cmdv)
{
    t_cmd_type cmd_type;
    t_func *exec_functions;
    int i;

    cmd_type = get_command_type(cmdv[0]);
    exec_functions = get_exec_functions();
    i = 0;
    while (i < TYPE_COUNT)
    {
        if (exec_functions[i].type == cmd_type)
            return (exec_functions[i].f(cmdv));
        i++;
    }
    printf("no exec function was executed for: [%s]\n", cmdv[0]);
    return (1);
}
