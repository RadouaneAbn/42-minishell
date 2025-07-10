/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_built_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:37:32 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/10 15:47:16 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	run_export(t_executable_data *data)
{
	int		status;
	char	**vec;

	vec = data->lst;
	vec++;
	if (vec[0] == NULL)
		return (print_exports(data->fd_out));
	status = EXIT_SUCCESS;
	while (*vec)
	{
		status |= pre_export(*vec);
		vec++;
	}
	return (status);
}

int	run_env(t_executable_data *data)
{
	char	**vec;

	vec = data->lst;
	vec++;
	return (print_env(data->fd_out));
}

int	run_unset(t_executable_data *data)
{
	int		status;
	char	**vec;

	vec = data->lst;
	vec++;
	status = EXIT_SUCCESS;
	while (*vec)
	{
		status |= unset(*vec);
		vec++;
	}
	return (status);
}

int	run_echo(t_executable_data *data)
{
	char	**vec;

	vec = data->lst;
	vec++;
	return (echo(vec, data->fd_out));
}

int	run_pwd(t_executable_data *data)
{
	char	*path;

	(void)data;
	if (data->fd_out == -1)
		data->fd_out = STDOUT_FILENO;
	path = expand_env("PWD");
	if (path[0] == '\0')
	{
		path = getcwd(NULL, 0);
		if (path == NULL)
			return (perror("minishell: getcwd"), EXIT_FAILURE);
		ft_putendl_fd(path, data->fd_out);
		free(path);
	}
	else
		ft_putendl_fd(path, data->fd_out);
	return (EXIT_SUCCESS);
}
