/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:32:32 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/10 19:04:31 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <minishell.h>

# define CMD_NOT_FOUND "command not found"

typedef enum e_cmd_type	t_cmd_type;

typedef struct s_fds
{
	int					prev;
	int					fd_in;
	int					fd_out;
	int					pipe[2];
}						t_fds;

typedef struct s_executable_data
{
	char				**lst;
	t_tree				*fd_tree;
	int					fd_in;
	int					fd_out;
}						t_executable_data;

typedef int				(*t_func_ptr)(t_executable_data *data);

void					execute_tree(t_tree *tree);
void					execute_command(char **cmd, t_tree *tree);
void					execute_command_2(char **cmdv, t_tree *tree);
int						run_executable(t_executable_data *data);
int						get_exit_status(void);
void					set_exit_status(int status);
void					store_child_exit_status(int status);

/* Redirection handling functions */
int						redirect_input(char *path, t_executable_data *data);
int						redirect_output(char *path, t_executable_data *data);
int						append_output(char *path, t_executable_data *data);
int						here_doc_input(char *path, t_executable_data *data);
int						handle_redirections(t_tree *tree,
							t_executable_data *data);

/* Pipe */
void					run_pipe_line(t_tree *tree);
bool					is_piped(t_tree *tree);

/* execution utils */
t_cmd_type				get_command_type(char *cmd);
t_func_ptr				*get_exec_functions(void);
void					init_executable_data(t_executable_data *data);
int						get_fd_out(t_tree *tree, t_fds fds);
bool					sibling_is_and_or(t_tree *tree);
bool					is_compound_command_or_pipeline(t_tree *tree);
bool					should_execute_next_tree(int pipe_type);
bool					tree_is_subshell(t_tree *tree);

#endif