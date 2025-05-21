#ifndef PARSER_H
#define PARSER_H

#include <lexer.h>
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
void    parse_simple_command(t_token_lst        *token_lst);
#endif
