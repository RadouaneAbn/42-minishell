/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:48:45 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/11 02:41:31 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


// static char *copy_string2(char *src)
// {
// 	char *value;
// 	int slen;

// 	slen = ft_strlen(src);
// 	value = gc_malloc(slen + 1);
// 	ft_strlcpy(value, src, slen + 1);
// 	return (value);
// }

// static char **tree_to_array(t_tree *tree)
// {
// 	char **arr;
// 	int i;
// 	t_tree *tmp;

// 	tmp = tree;
// 	i = 0;
// 	while (tmp)
// 	{
// 		i++;
// 		tmp = tmp->next;
// 	}
// 	arr = gc_malloc((sizeof(char *)) * (i + 1));
// 	i = 0;
// 	while (tree)
// 	{
// 		arr[i++] = copy_string2(tree->data);
// 		tree = tree->next;
// 	}
// 	arr[i] = NULL;
// 	return arr;
// }

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

// < /dev/stdin cat | ls > /dev/stdout

pid_t	execute_command_tree_piped(t_tree *tree, t_fds fds)
{
	char	**cmd_array;
	pid_t	pid;

	if (tree->data_type == T_CMD_ARG)
		// cmd_array = tree_to_array(tree);
		cmd_array = tree_expand_simple_command(tree);
	else
	{
		cmd_array = gc_malloc(sizeof(char *));
		cmd_array[0] = NULL;
	}
	pid = fork();
	if (pid == 0)
	{
		*ps_status() = false;
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
