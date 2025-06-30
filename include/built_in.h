#ifndef BUILT_IN_H
#define BUILT_IN_H

#include <hashmap.h>
#include <execution.h>

typedef enum e_cmd_type
{
    RUN_EXPORT,
    RUN_ENV,
    RUN_UNSET,
    RUN_ECHO,
    RUN_PWD,
    RUN_CD,
    RUN_EXIT,
    RUN_EXECUTABLE,
    TYPE_COUNT
} t_cmd_type;

/* echo flag */
#define NO_FLAG 0
#define NO_NL 1
/* cd */
#define CUR 0
#define PAR 1

t_map   *get_map();
char **split_export_args(char *arg);

int     echo(char **vec, int fd);
int     export(char *key, char *value);
int     unset(char *key);
char    *expand_env(char *key);
int     pre_export(char *exported);

int print_env(int fd);
int print_exports(int fd);

int run_export(t_executable_data *data);
int run_env(t_executable_data *data);
int run_unset(t_executable_data *data);
int run_echo(t_executable_data *data);
int run_pwd(t_executable_data *data);
int run_cd(t_executable_data *data);
int run_exit(t_executable_data *data);

t_cmd_type get_command_type (char *cmd);

#endif