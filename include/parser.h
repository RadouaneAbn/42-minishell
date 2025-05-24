#ifndef PARSER_H
#define PARSER_H

#include <minishell.h>
/* MAIN FILE STRUCTURE*/
typedef struct s_file t_file;
struct s_file
{
	t_file *next;
	char	*file_name;
	int	operation_type; //like FILE_APPEND, FILE_TRUCATE, FILE_READ, HERE_DOC_READ
};

/* MAIN COMMAND STRUCT */
typedef struct s_cmd t_cmd;
struct s_cmd
{
	t_list *cmd_arg;
	//t_file infiles;
	//t_file outfiles;
};

/* MAIN AST STRUCT */
typedef struct s_tree t_tree;
struct s_tree
{
	t_tree	*next;
	t_tree	*sibling;
	int	data_type;
	void	*data;
};

t_tree	*parser(t_token_lst *token_lst);
void	get_subshell(t_token_lst	**token_lst);
//void    parse_simple_command(t_token_lst        *token_lst);


/* TREE */
t_tree *tree_create_new(int data_type, void *parameter);
t_tree	*tree_get_last(t_tree *tree);
void	tree_add_back(t_tree **head, t_tree *new);
t_tree	*tree_get_last_sibling(t_tree *tree);
void	tree_add_sibling_back(t_tree **head, t_tree *new);


/* parsing functions*/
t_tree	*tree_get_argument(t_token_lst	**token_lst);
t_tree	*tree_get_io_redirect(t_token_lst	**token_lst);
bool	is_output_redirection_operator(int	operator);
bool	is_input_redirection_operator(int	operator);
bool	is_token_word(int	operator);
t_tree	*parse_simple_command(t_token_lst	**token_lst);
void	print_tree(t_tree *tree);

void	consume(t_token_lst **token_lst);
t_tree	*tree_get_command(t_token_lst **token_lst);
#endif
