/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:48:45 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/16 16:09:06 by hsacr            ###   ########.fr       */
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

pid_t	execute_command_tree_piped(t_tree *tree, t_fds fds)
{
	char	**cmd_array;
	t_tree	*fd_start;
	pid_t	pid;

	fd_start = get_command_from_tree(tree, &cmd_array);
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
			execute_command_piped(cmd_array, fd_start, fds);
		}
	}
	return (pid);
}

int	create_pipe(t_tree *tree, int (*fd)[2])
{
	*fd[0] = -1;
	*fd[1] = -1;
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

void	organize_fds(t_fds *fds, t_tree *tree)
{
	if (fds->prev != -1)
		close(fds->prev);
	if (tree->sibling)
		fds->prev = fds->pipe[0];
	else if (fds->pipe[0] != -1)
		close(fds->pipe[0]);
	if (fds->pipe[1] != -1)
		close(fds->pipe[1]);
}

void	run_pipe_line(t_tree *tree)
{
	pid_t	last_pid;
	t_fds	fds;

	fds = (t_fds){.prev = -1, .fd_in = STDIN_FILENO, .fd_out = STDOUT_FILENO};
	while (tree)
	{
		gc_level_init();
		if (create_pipe(tree, &fds.pipe) == -1)
		{
			free_level();
			return ;
		}
		if (fds.prev != -1)
			fds.fd_in = fds.prev;
		fds.fd_out = get_fd_out(tree, fds);
		last_pid = execute_command_tree_piped(tree->next, fds);
		organize_fds(&fds, tree);
		tree = tree->sibling;
		free_level();
	}
	wait_for_children(last_pid);
}
