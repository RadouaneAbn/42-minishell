#ifndef BUILT_IN_H
#define BUILT_IN_H

#include <hashmap.h>

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

t_map   *get_map();
char **split_export_args(char *arg);

int     echo(char **vec);
int     export(char *key, char *value);
int     unset(char *key);
char    *expand_env(char *key);
int     pre_export(char *exported);
int print_env();
int print_exports();

int run_export(char **vec);
int run_env(char **vec);
int run_unset(char **vec);
int run_echo(char **vec);
int run_pwd(char **vec);
int run_cd(char **vec);
int run_exit(char **vec);

#endif