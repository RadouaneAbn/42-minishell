/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radouane <radouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:48:45 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/15 04:27:23 by radouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute_command_piped(char **cmdv, t_tree *tree, t_fds fds)
{
	t_cmd_type			cmd_type;
	t_func_ptr			*exec_functions;
	t_executable_data	data;
	int					status;

	cmd_type = get_command_type(cmdv[0]);
	exec_functions = get_exec_functions();
	data = (t_executable_data){NULL, NULL, fds.fd_in, fds.fd_out};
	if (handle_redirections(tree, &data) == -1)
		clean_exit(1);
	if (fds.pipe[0] != -1)
		close(fds.pipe[0]);
	data.lst = cmdv;
	data.fd_tree = tree;
	status = exec_functions[cmd_type](&data);
	clean_exit(status);
}

void	execute_subshell_piped(t_tree *tree, t_fds fds)
{
	t_cmd_type			cmd_type;
	t_func_ptr			*exec_functions;
	t_executable_data	data;
	int					status;

	data = (t_executable_data){NULL, NULL, fds.fd_in, fds.fd_out};
	if (handle_redirections(tree->sibling, &data) == -1)
		clean_exit(1);
	if (fds.pipe[0] != -1)
		close(fds.pipe[0]);
	execute_tree(tree->next);
	clean_exit(get_exit_status());
}

pid_t	execute_command_tree_piped(t_tree *tree, t_fds fds)
{
	char	**cmd_array;
	pid_t	pid;
	int status;

	if (tree->data_type == T_CMD_ARG)
		cmd_array = expand_simple_command_lst(tree);
	else if (tree->data_type == T_SUBSHELL)
		cmd_array = NULL;
	else
	{
		cmd_array = gc_malloc(sizeof(char *));
		cmd_array[0] = NULL;
	}
	if (tree->data_type == T_SUBSHELL)
	{
		pid = fork();
		if (pid == 0)
			execute_subshell_piped(tree, fds);
	}
	else
	{
		pid = fork();	
		if (pid == 0)
		{
			*ps_status() = false;
			if (tree->data_type == T_CMD_ARG)
				execute_command_piped(cmd_array, tree->sibling, fds);
			else
				execute_command_piped(cmd_array, tree, fds);
		}
	}
	return (pid);
}

void	wait_for_children(pid_t last_pid)
{
	int		status;
	pid_t	wpid;

	wpid = waitpid(-1, &status, 0);
	while (wpid > 0)
	{
		if (wpid == last_pid)
			store_child_exit_status(status);
		wpid = waitpid(-1, &status, 0);
	}
}

int	create_pipe(t_tree *tree, int (*fd)[2])
{
	if (tree->sibling)
	{
		if (pipe(*fd) == -1)
		{
			perror("minishell: pipe");
			return (-1);
		}
	}
	return (0);
}

pid_t	execute_tree_subshell(t_tree *tree);

void	run_pipe_line(t_tree *tree)
{
	pid_t	last_pid;
	t_fds	fds;

	fds.fd_in = STDIN_FILENO;
	fds.fd_out = STDOUT_FILENO;
	fds.prev = -1;
	while (tree)
	{
		gc_level_init();
		fds.pipe[0] = -1;
		fds.pipe[1] = -1;
		if (create_pipe(tree, &fds.pipe) == -1)
		{
			free_level();
			return ;
		}
		if (fds.prev != -1)
			fds.fd_in = fds.prev;
		fds.fd_out = get_fd_out(tree, fds);
		last_pid = execute_command_tree_piped(tree->next, fds);
		if (fds.prev != -1)
			close(fds.prev);
		if (tree->sibling)
			fds.prev = fds.pipe[0];
		else if (fds.pipe[0] != -1)
			close(fds.pipe[0]);
		if (fds.pipe[1] != -1)
			close(fds.pipe[1]);
		tree = tree->sibling;
		free_level();
	}
	wait_for_children(last_pid);
}
