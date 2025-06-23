#ifndef EXECUTION_H
#define EXECUTION_H

#include <parser.h>

typedef struct s_func
{
	t_cmd_type	type;
	int		(*f)(char **);
}			t_func;

void execute_tree(t_tree *tree);
int execute_command(char **cmd);
int run_executable(char **vec);

#endif