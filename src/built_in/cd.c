/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:37:19 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/10 15:37:20 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	run_cd(t_executable_data *data)
{
	char	**vec;
	char	*new_path;
	char	*path;

	vec = data->lst;
	if (vec[1] != NULL && vec[2] != NULL)
		return (print_error("cd", NULL, NULL, "too many arguments"), 1);
	if (vec[1])
		path = vec[1];
	else if (vec[1] == NULL)
	{
		path = expand_env("HOME");
		if (path == NULL)
			return (print_error("cd", NULL, NULL, "HOME not set"), 1);
	}
	if (chdir(path) != 0)
		return (perror("minishell: cd"), EXIT_FAILURE);
	new_path = getcwd(NULL, 0);
	if (new_path == NULL)
		perror("minishell: getcwd");
	export("OLDPWD", expand_env("PWD"));
	if (new_path)
		export("PWD", new_path);
	free(new_path);
	return (EXIT_SUCCESS);
}
