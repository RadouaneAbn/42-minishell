/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:48:34 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/10 15:51:34 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	sibling_is_and_or(t_tree *tree)
{
	if (tree->sibling)
	{
		if (tree->sibling->data_type == T_AND
			|| tree->sibling->data_type == T_OR)
			return (TRUE);
	}
	return (FALSE);
}

bool	is_compound_command_or_pipeline(t_tree *tree)
{
	return (tree->data_type == T_COMPOUND_COMMAND
		|| tree->data_type == T_PIPELINE);
}

bool	should_execute_next_tree(int pipe_type)
{
	int	last_exit_code;

	if (pipe_type == T_COMMAND)
		return (TRUE);
	last_exit_code = get_info()->last_exit_status;
	if (pipe_type == T_AND && last_exit_code == 0)
		return (TRUE);
	if (pipe_type == T_OR && last_exit_code != 0)
		return (TRUE);
	return (FALSE);
}

bool	tree_is_subshell(t_tree *tree)
{
	return (tree->next && tree->next->data_type == T_SUBSHELL);
}

bool	is_piped(t_tree *tree)
{
	return (tree->data_type == T_COMMAND && tree->sibling != NULL);
}
