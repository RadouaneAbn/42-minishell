/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_built_in_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:37:32 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/11 01:15:14 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	run_exit(t_executable_data *data)
{
	char	**vec;
	char	*exit_str;
	long	exit_status;

	vec = data->lst;
	exit_str = vec[1];
	if (exit_str == NULL)
		exit_status = get_exit_status();
	else
	{
		exit_status = convert_exist_status(exit_str);
		if (exit_status == -1)
		{
			print_error("exit", NULL, exit_str, "numeric argument required");
			exit_status = 2;
		}
	}
	free_full();
	exit(exit_status);
}

int	execute_command_exec(t_executable_data *data)
{
	char	**vec;

	vec = data->lst;
	if (has_exec_perm(data->lst[0]) == false)
	{
		print_error(data->lst[0], NULL, NULL, "Permission denied");
		exit(126);
	}
	if (is_dir(data->lst[0]) == true)
	{
		print_error(data->lst[0], NULL, NULL, "Is a directory");
		exit(126);
	}
	if (execve(vec[0], vec, build_env()) == -1)
	{
		perror("minishell: execve");
		exit(1);
	}
	return (TRUE);
}

int	run_executable(t_executable_data *data)
{
	char	**vec;

	vec = data->lst;
	// if (data->fd_in != -1 && data->fd_in != STDIN_FILENO)
	// {
	// 	dup2(data->fd_in, STDIN_FILENO);
	// 	close(data->fd_in);
	// }
	// if (data->fd_out != -1 && data->fd_out != STDOUT_FILENO)
	// {
	// 	dup2(data->fd_out, STDOUT_FILENO);
	// 	close(data->fd_out);
	// }
	if (vec[0] == NULL)
		exit(0);
	if (command_is_empty(vec[0]))
		exit(127);
	if (ft_strchr(vec[0], '/') == NULL)
		vec[0] = find_file(vec[0]);
	return (execute_command_exec(data));
}
