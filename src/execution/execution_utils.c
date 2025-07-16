/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radouane <radouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:48:31 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/16 16:26:46 by radouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	*ps_status(void)
{
	static bool	is_main = true;

	return (&is_main);
}

t_cmd_type	get_command_type(char **cmd)
{
	static char	*built_ins[8] = {"export", "env", "unset", "echo", "pwd", "cd",
		"exit", NULL};
	int			i;

	if (cmd == NULL || cmd[0] == NULL)
		return (RUN_EXECUTABLE);
	i = RUN_EXPORT;
	while (built_ins[i])
	{
		if (ft_strcmp(built_ins[i], cmd[0]) == 0)
			break ;
		i++;
	}
	return (i);
}

t_func_ptr	*get_exec_functions(void)
{
	static t_func_ptr	exec_functions[8] = {run_export, run_env, run_unset,
		run_echo, run_pwd, run_cd, run_exit, run_executable};

	return (exec_functions);
}

int	get_fd_out(t_tree *tree, t_fds fds)
{
	if (tree->sibling)
		return (fds.pipe[1]);
	else
		return (STDOUT_FILENO);
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
