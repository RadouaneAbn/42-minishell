/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 00:16:43 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/16 16:04:38 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute_subshell_piped(t_tree *tree, t_fds fds)
{
	t_executable_data	data;

	data = (t_executable_data){NULL, NULL, fds.fd_in, fds.fd_out};
	if (handle_redirections(tree->sibling, &data) == -1)
		clean_exit(1);
	if (fds.pipe[0] != -1)
		close(fds.pipe[0]);
	execute_tree(tree->next);
	clean_exit(get_exit_status());
}

void	run_subshell(t_tree *tree)
{
	t_executable_data	data;

	*ps_status() = false;
	data = (t_executable_data){NULL, NULL, -1, -1};
	if (handle_redirections(tree->sibling, &data) == -1)
		clean_exit(1);
	execute_tree(tree->next);
	clean_exit(get_exit_status());
}

pid_t	execute_tree_subshell(t_tree *tree)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		run_subshell(tree);
	else
	{
		waitpid(pid, &status, 0);
		store_child_exit_status(status);
	}
	return (pid);
}
