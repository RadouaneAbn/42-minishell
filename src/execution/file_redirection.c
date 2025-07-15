/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 00:15:13 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/16 00:15:25 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	node_isfile(int data_type)
{
	if (data_type == T_FILE_APPEND || data_type == T_FILE_HERE_DOC
		|| data_type == T_FILE_READ || data_type == T_FILE_TRUNCATE)
		return (true);
	return (false);
}

void	dup_pipe(int fd_in, int fd_out)
{
	if (fd_in != -1 && fd_in != STDIN_FILENO)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out != -1 && fd_out != STDOUT_FILENO)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
}

int	handle_file_redirection(t_tree *tree, char *filename)
{
	if (tree->data_type == RED_IN)
		return (redirect_input(filename));
	else if (tree->data_type == RED_OUT)
		return (redirect_output(filename));
	else if (tree->data_type == APPEND_OUT)
		return (append_output(filename));
	else if (tree->data_type == HERE_DOC)
		return (here_doc_input(filename));
	return (-1);
}

int	handle_redirections(t_tree *tree, t_executable_data *data)
{
	int		status;
	char	*filename;
	bool	ambiguous;

	dup_pipe(data->fd_in, data->fd_out);
	if (tree && !node_isfile(tree->data_type))
		return (-1);
	while (tree)
	{
		filename = expand_redirection(tree->data, &ambiguous);
		if (ambiguous)
		{
			write(2, "ambiguous redirect", 19);
			return (-1);
		}
		if (handle_file_redirection(tree, filename) == -1)
			return (-1);
		tree = tree->next;
	}
	return (0);
}
