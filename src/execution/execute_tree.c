/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:48:34 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/11 01:48:08 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char *copy_string2(char *src)
{
	char *value;
	int slen;

	slen = ft_strlen(src);
	value = gc_malloc(slen + 1);
	ft_strlcpy(value, src, slen + 1);
	return (value);
}

static char **tree_to_array(t_tree *tree)
{
	char **arr;
	int i;
	t_tree *tmp;

	tmp = tree;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	arr = gc_malloc((sizeof(char *)) * (i + 1));
	i = 0;
	while (tree)
	{
		arr[i++] = copy_string2(tree->data);
		tree = tree->next;
	}
	arr[i] = NULL;
	return arr;
}

void	execute_command_tree(t_tree *tree)
{
	char	**cmd_array;
	int		status;
	pid_t	pid;

	// cmd_array = tree_expand_simple_command(tree);
	cmd_array = tree_to_array(tree);
	pid = -1;
	if (get_command_type((char *)tree->data) == RUN_EXECUTABLE)
		pid = fork();
	else
		execute_command_2(cmd_array, tree->sibling);
	if (pid == 0)
		execute_command(cmd_array, tree->sibling);
	if (pid != -1)
	{
		waitpid(pid, &status, 0);
		store_child_exit_status(status);
	}
}

void	run_subshell(t_tree *tree)
{
	t_executable_data	data;

	init_executable_data(&data);
	if (handle_redirections(tree->sibling, &data) == -1)
		exit(1);
	if (data.fd_in != -1)
	{
		dup2(data.fd_in, STDIN_FILENO);
		close(data.fd_in);
	}
	if (data.fd_out != -1)
	{
		dup2(data.fd_out, STDOUT_FILENO);
		close(data.fd_out);
	}
	execute_tree(tree->next);
	exit(get_exit_status());
}

void	execute_tree_subshell(t_tree *tree)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
		run_subshell(tree);
	else
	{
		waitpid(pid, &status, 0);
		store_child_exit_status(status);
	}
}

void	start_tree_execution(t_tree *tree)
{
	gc_level_init();
	if (tree_is_subshell(tree))
	{
		execute_tree_subshell(tree->next);
	}
	else
	{
		if (is_piped(tree) == TRUE)
			run_pipe_line(tree);
		else
			execute_command_tree(tree->next);
	}
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
			break;
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
