/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radouane <radouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:48:31 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/16 16:44:05 by radouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute_command(char **cmdv, t_tree *tree)
{
	t_cmd_type			cmd_type;
	t_func_ptr			*exec_functions;
	t_executable_data	data;
	int					status;

	signal(SIGINT, SIG_DFL);
	cmd_type = get_command_type(cmdv);
	exec_functions = get_exec_functions();
	data = (t_executable_data){NULL, NULL, -1, -1};
	if (handle_redirections(tree, &data) != -1)
	{
		data.lst = cmdv;
		data.fd_tree = tree;
		status = exec_functions[cmd_type](&data);
	}
	else
		status = 1;
	clean_exit(status);
}

void	execute_command_2(char **cmdv, t_tree *tree)
{
	t_cmd_type			cmd_type;
	t_func_ptr			*exec_functions;
	t_executable_data	data;
	t_fds				bak;
	int					status;

	cmd_type = get_command_type(cmdv);
	exec_functions = get_exec_functions();
	data = (t_executable_data){NULL, NULL, -1, -1};
	bak.fd_in = dup(STDIN_FILENO);
	bak.fd_out = dup(STDOUT_FILENO);
	if (handle_redirections(tree, &data) != -1)
	{
		data = (t_executable_data){cmdv, tree, bak.fd_in, bak.fd_out};
		status = exec_functions[cmd_type](&data);
	}
	else
		status = 1;
	dup2(bak.fd_in, STDIN_FILENO);
	dup2(bak.fd_out, STDOUT_FILENO);
	close(bak.fd_in);
	close(bak.fd_out);
	set_exit_status(status);
}
