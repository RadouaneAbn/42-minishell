/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:12:05 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/16 21:41:01 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <minishell.h>
/* MAIN FILE STRUCTURE*/
typedef struct s_file	t_file;
struct					s_file
{
	t_file	*next;
	char	*file_name;
	int		operation_type;
};

/* MAIN AST STRUCT */
typedef struct s_tree	t_tree;
struct					s_tree
{
	t_tree				*next;
	t_tree				*sibling;
	int					data_type;
	void				*data;
};

/*MAIN STUCTURE OF TOKEN TYPES*/
typedef enum e_type
{
	T_COMPOUND_COMMAND,
	T_PIPELINE,
	T_FILE_HERE_DOC,
	T_FILE_APPEND,
	T_FILE_READ,
	T_FILE_TRUNCATE,
	T_AND,
	T_OR,
	T_COMMAND,
	T_SUBSHELL,
	T_CMD_ARG,
}	t_type;

t_tree					*parser(t_token_lst *token_lst);
void					get_subshell(t_token_lst	**token_lst);
t_tree					*parser(t_token_lst *token_lst);
void					get_subshell(t_token_lst **token_lst);

/* TREE */
t_tree					*tree_create_new(int data_type, void *parameter);
t_tree					*tree_get_last(t_tree *tree);
void					tree_add_back(t_tree **head, t_tree *new);
t_tree					*tree_get_last_sibling(t_tree *tree);
void					tree_add_sibling_back(t_tree **head, t_tree *new);
int						tree_get_size(t_tree *list);

/* parsing functions*/
t_tree					*tree_get_argument(t_token_lst **token_lst);
t_tree					*tree_get_io_redirect(t_token_lst **token_lst);
bool					is_output_redirection_operator(int operator);
bool					is_input_redirection_operator(int operator);
bool					is_redirect_operator(int operator);
bool					is_token_word(int operator);
t_tree					*tree_get_simple_command(t_token_lst **token_lst);
void					print_tree(t_tree *tree, int n);

void					consume(t_token_lst **token_lst);
t_tree					*tree_get_command(t_token_lst **token_lst);
t_tree					*tree_get_pipeline(t_token_lst **token_lst);
t_tree					*tree_get_compound_command(t_token_lst **token_lst);
char					*here_doc(char *delimiter);
void					free_tree(t_tree **tree);
#endif
