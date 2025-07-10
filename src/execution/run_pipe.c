/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:48:45 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/10 16:02:09 by rabounou         ###   ########.fr       */
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
	init_executable_data(&data);
	if (handle_redirections(tree, &data) == -1)
		exit(1);
	if (data.fd_in == -1)
		data.fd_in = fds.fd_in;
	if (data.fd_out == -1)
		data.fd_out = fds.fd_out;
	if (fds.pipe[0] != -1)
		close(fds.pipe[0]);
	data.lst = cmdv;
	data.fd_tree = tree;
	status = exec_functions[cmd_type](&data);
	exit(status);
}

pid_t	execute_command_tree_piped(t_tree *tree, t_fds fds)
{
	char	**cmd_array;
	pid_t	pid;

	if (tree->data_type == T_CMD_ARG)
		cmd_array = tree_expand_simple_command(tree);
	else
	{
		cmd_array = malloc(sizeof(char *));
		cmd_array[0] = NULL;
	}
	pid = fork();
	if (pid == 0)
	{
		if (tree->data_type == T_CMD_ARG)
			execute_command_piped(cmd_array, tree->sibling, fds);
		else
			execute_command_piped(cmd_array, tree, fds);
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

void	run_pipe_line(t_tree *tree)
{
	pid_t	last_pid;
	t_fds	fds;

	fds.fd_in = STDIN_FILENO;
	fds.fd_out = STDOUT_FILENO;
	fds.prev = -1;
	while (tree)
	{
		fds.pipe[0] = -1;
		fds.pipe[1] = -1;
		if (create_pipe(tree, &fds.pipe) == -1)
			return ;
		if (fds.prev != -1)
			fds.fd_in = fds.prev;
		fds.fd_out = get_fd_out(tree, fds);
		last_pid = execute_command_tree_piped(tree->next, fds);
		if (fds.prev != -1)
			close(fds.prev);
		if (tree->sibling)
			fds.prev = fds.pipe[0];
		if (fds.pipe[1] != -1)
			close(fds.pipe[1]);
		tree = tree->sibling;
	}
	wait_for_children(last_pid);
}
