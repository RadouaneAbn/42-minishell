/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:48:31 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/16 00:32:00 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_tree	*get_command_from_tree(t_tree *tree, char ***cmdv)
{
	t_tree	*fd_start;

	fd_start = NULL;
	if (tree->data_type == T_CMD_ARG)
	{
		*cmdv = expand_simple_command_lst(tree);
		fd_start = tree->sibling;
	}
	else if (tree->data_type == T_SUBSHELL)
		*cmdv = NULL;
	else
	{
		*cmdv = gc_malloc(sizeof(char *));
		*cmdv[0] = NULL;
		fd_start = tree;
	}
	return (fd_start);
}
