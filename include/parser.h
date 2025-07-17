/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:12:05 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/17 10:08:28 by hsacr            ###   ########.fr       */
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

void	put_unexpected_token_err(char *error);
t_tree	*parser(t_token_lst *token_lst);
void	consume(t_token_lst **token_lst);
bool	is_token_word(int operator);
bool	is_output_redirection_operator(int operator);
bool	is_input_redirection_operator(int operator);
bool	is_redirect_operator(int operator);
t_tree	*tree_get_io_redirect_list(t_token_lst	**token_lst);
bool	tree_set_command(t_token_lst **token_lst, t_tree **command);
t_tree	*tree_get_command(t_token_lst **token_lst);
t_type	get_pipeline_relation(t_token_type	type);
bool	tree_set_compound_command(t_token_lst **token_lst,
			t_tree **compound_command);
t_tree	*tree_get_compound_command(t_token_lst **token_lst);
bool	tree_set_pipeline(t_token_lst **token_lst, t_tree **pipeline);
t_tree	*tree_get_pipeline(t_token_lst **token_lst);
t_tree	*tree_get_argument(t_token_lst	**token_lst);
bool	tree_set_io_redirect(t_token_lst	**token_lst,
			t_tree **new_io_redirect, int data_type, char *parameter);
t_tree	*tree_get_io_redirect(t_token_lst	**token_lst);
bool	tree_set_simple_command(t_token_lst **token_lst,
			t_tree **tree_ptr, t_tree *(tree_func)(t_token_lst **));
t_tree	*tree_get_simple_command(t_token_lst	**token_lst);
bool	tree_set_subshell_redirect(t_token_lst	**token_lst, t_tree **subshell);
void	throw_unclosed_brace_err(void);
bool	tree_set_subshell(t_token_lst	**token_lst, t_tree **subshell);
t_tree	*parse_subshell(t_token_lst	**token_lst);
#endif
