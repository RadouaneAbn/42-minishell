/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:48:31 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/10 15:53:35 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	handle_redirections(t_tree *tree, t_executable_data *data)
{
	int	status;

	if (data->fd_in != -1 && data->fd_in != STDIN_FILENO)
	{
		dup2(data->fd_in, STDIN_FILENO);
		close(data->fd_in);
	}
	if (data->fd_out != -1 && data->fd_out != STDOUT_FILENO)
	{
		dup2(data->fd_out, STDOUT_FILENO);
		close(data->fd_out);
	}
	while (tree)
	{
		if (tree->data_type == RED_IN)
			status = redirect_input((char *)tree->data, data);
		else if (tree->data_type == RED_OUT)
			status = redirect_output((char *)tree->data, data);
		else if (tree->data_type == APPEND_OUT)
			status = append_output((char *)tree->data, data);
		else if (tree->data_type == HERE_DOC)
			status = here_doc_input((char *)tree->data, data);
		if (status == -1)
			return (-1);
		tree = tree->next;
	}
	return (0);
}

void	execute_command(char **cmdv, t_tree *tree)
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
	data.lst = cmdv;
	data.fd_tree = tree;
	status = exec_functions[cmd_type](&data);
	exit(status);
}

void	execute_command_2(char **cmdv, t_tree *tree)
{
	t_cmd_type			cmd_type;
	t_func_ptr			*exec_functions;
	t_executable_data	data;
	int					status;

	cmd_type = get_command_type(cmdv[0]);
	exec_functions = get_exec_functions();
	init_executable_data(&data);
	if (handle_redirections(tree, &data) == -1)
	{
		set_exit_status(1);
		return ;
	}
	data.lst = cmdv;
	data.fd_tree = tree;
	status = exec_functions[cmd_type](&data);
	set_exit_status(status);
}
