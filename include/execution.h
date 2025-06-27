#ifndef EXECUTION_H
#define EXECUTION_H

#include <parser.h>


# define CMD_NOT_FOUND "command not found"


typedef struct s_executable_data
{
    char **lst;
    t_tree *fds;
    int fd_in;
    int fd_out;
} t_executable_data;

typedef int (*t_func_ptr)(char **);

void execute_tree(t_tree *tree);
int execute_command(char **cmd, t_tree *tree);
int run_executable(char **vec);

/* Redirection handling functions */
int redirect_input(char *path, t_executable_data *data);
int redirect_output(char *path, t_executable_data *data);
int append_output(char *path, t_executable_data *data);
int here_doc_input(char *path, t_executable_data *data);

#endif