#ifndef EXECUTION_H
#define EXECUTION_H

#include <parser.h>
# include <sys/wait.h>
# include <built_in.h>


# define CMD_NOT_FOUND "command not found"


typedef struct s_executable_data
{
    char **lst;
    t_tree *fds;
    int fd_in;
    int fd_out;
} t_executable_data;

typedef int (*t_func_ptr)(t_executable_data *data);

void execute_tree(t_tree *tree);
void execute_command(char **cmd, t_tree *tree);
void execute_command_2(char **cmdv, t_tree *tree);
int run_executable(t_executable_data *data);

int get_exit_status(void);
void set_exit_status(int status);

/* Redirection handling functions */
int redirect_input(char *path, t_executable_data *data);
int redirect_output(char *path, t_executable_data *data);
int append_output(char *path, t_executable_data *data);
int here_doc_input(char *path, t_executable_data *data);

/* Printing errors */
int print_cmd_error(char *error);

/* Pipe */
void run_pipe_line(t_tree *tree);

t_func_ptr *get_exec_functions(void);
int handle_redirections(t_tree *tree, t_executable_data *data);
void init_executable_data(t_executable_data *data);
char **get_full_command_from_tree(t_tree *tree);

#endif