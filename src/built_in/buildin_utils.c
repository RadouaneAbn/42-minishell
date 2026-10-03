/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radouane <radouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:44:57 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/14 22:43:45 by radouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	command_is_empty(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] != ' ')
			return (FALSE);
		i++;
	}
	print_error(cmd, NULL, NULL, "command not found");
	return (TRUE);
}

char	*get_path_from_env(void)
{
	char	*path;

	path = expand_env("PATH");
	if (path[0] == '\0')
		return (NULL);
	return (path);
}

char	*join_path(char *path, char *cmd)
{
	int		t_size;
	char	*str;

	t_size = ft_strlen(path) + ft_strlen(cmd) + 2;
	str = gc_malloc(t_size * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[0] = 0;
	ft_strlcat(str, path, t_size);
	ft_strlcat(str, "/", t_size);
	ft_strlcat(str, cmd, t_size);
	return (str);
}

// bool	file_exist(char *path)
// {
// 	if (access(path, F_OK) == 0)
// 		return (TRUE);
// 	return (FALSE);
// }

char	*find_file(char *cmd)
{
	char	**path;
	char	*path_env;
	char	*cmd_abs_path;
	int		i;

	path_env = get_path_from_env();
	if (path_env == NULL)
		return (cmd);
	path = ft_split(path_env, ':');
	i = 0;
	while (path[i])
	{
		cmd_abs_path = join_path(path[i], cmd);
		if (file_exist(cmd_abs_path) == TRUE)
			return (cmd_abs_path);
		gc_local_free(cmd_abs_path);
		i++;
	}
	print_error(cmd, NULL, NULL, "command not found");
	clean_exit(127);
	return (0);
}
