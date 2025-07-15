/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:48:34 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/16 00:31:31 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// static t_tree	*get_command_from_tree(t_tree *tree, char ***cmdv)
// {
// 	t_tree	*fd_start;

// 	fd_start = NULL;
// 	if (tree->data_type == T_CMD_ARG)
// 	{
// 		*cmdv = expand_simple_command_lst(tree);
// 		fd_start = tree->sibling;
// 	}
// 	else
// 	{
// 		*cmdv = gc_malloc(sizeof(char *));
// 		*cmdv[0] = NULL;
// 		fd_start = tree;
// 	}
// 	return (fd_start);
// }

void	execute_command_tree(t_tree *tree)
{
	t_tree	*fd_start;
	char	**cmd_array;
	int		status;
	pid_t	pid;

	fd_start = get_command_from_tree(tree, &cmd_array);
	pid = -1;
	if (get_command_type(cmd_array[0]) == RUN_EXECUTABLE)
	{
		signal(SIGINT, SIG_IGN);
		pid = fork();
		if (pid == -1)
			perror("fork");
	}
	else
		execute_command_2(cmd_array, fd_start);
	if (pid == 0)
		execute_command(cmd_array, fd_start);
	if (pid != -1)
	{
		waitpid(pid, &status, 0);
		store_child_exit_status(status);
		signal(SIGINT, sigint_handler);
	}
}

void	start_tree_execution(t_tree *tree)
{
	gc_level_init();
	if (is_piped(tree) == TRUE)
		run_pipe_line(tree);
	else if (tree_is_subshell(tree))
		execute_tree_subshell(tree->next);
	else
		execute_command_tree(tree->next);
	free_level();
}

void	execute_tree(t_tree *tree)
{
	int	pipe_type;

	pipe_type = T_COMMAND;
	while (tree)
	{
		if (is_compound_command_or_pipeline(tree) == TRUE)
		{
			if (should_execute_next_tree(pipe_type) == TRUE)
				execute_tree(tree->next);
		}
		else if (tree->data_type == T_COMMAND)
		{
			start_tree_execution(tree);
			pipe_type = T_COMMAND;
			break ;
		}
		if (sibling_is_and_or(tree) == TRUE)
		{
			pipe_type = tree->sibling->data_type;
			tree = tree->sibling;
		}
		if (tree)
			tree = tree->sibling;
	}
}
