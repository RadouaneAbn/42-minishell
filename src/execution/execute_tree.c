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
        args[i] = ft_strdup((char *) tree->data);
        tree = tree->next;
        i++;
    }
    args[i] = NULL;
    return (args);
}

int execute_command_tree(t_tree *tree)
{
    char **cmd_array;
    
    cmd_array = get_full_command_from_tree(tree);
    // print_args_list(cmd_array);
    return (execute_command(cmd_array));
}

void print_sib(t_tree *tree)
{
	char *data_type[11];
	data_type[T_COMPOUND_COMMAND]="COMPOUND COMMAND";
	data_type[T_FILE_HERE_DOC]="FILE_HERE_DOC";
	data_type[T_FILE_APPEND]="FILE_APPEND";
	data_type[T_FILE_READ]="FILE_READ";
	data_type[T_FILE_TRUNCATE]="FILE_TRUNCATE";
	data_type[T_CMD_ARG]="CMD ARG";
	data_type[T_AND]="AND";
	data_type[T_OR]="OR";
	data_type[T_COMMAND]="COMMAND";
	data_type[T_SUBSHELL]="SUBSHELL";
	data_type[T_PIPELINE]="PIPELINE";

    printf("sib: [%p]\n", tree);
    if (tree)
        printf("type: [%s]\n", data_type[tree->data_type]);
    else
        printf("type: [null]\n");
}

/*
ls || pwd || cat && hey
*/

void execute_tree(t_tree *tree)
{
    t_info *info;
    int pipe_type;

    info = get_info();
    pipe_type = T_COMMAND;
    info->last_exit_status = 0;
    while (tree)
    {
        if (tree->data_type == T_COMPOUND_COMMAND || tree->data_type == T_PIPELINE)
        {
            if (pipe_type == T_COMMAND || (pipe_type == T_AND && info->last_exit_status == 0) || 
                (pipe_type == T_OR && info->last_exit_status != 0))
                execute_tree(tree->next);
        }
        else if (tree->data_type == T_COMMAND)
        {
            if (tree->next && tree->next->data_type == T_SUBSHELL)
                execute_tree(tree->next->next);
            else
                info->last_exit_status = execute_command_tree(tree->next);
            pipe_type = T_COMMAND;
        }
        if (tree->sibling != NULL && tree->sibling->data_type == T_AND)
        {
            pipe_type = T_AND;
            tree = tree->sibling;
        }
        else if (tree->sibling != NULL && tree->sibling->data_type == T_OR)
        {
            pipe_type = T_OR;
            tree = tree->sibling;
        }
        if (tree)
            tree = tree->sibling; 
    }
}
