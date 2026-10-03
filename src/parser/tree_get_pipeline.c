/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_get_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:35:15 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/16 11:07:02 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	tree_set_pipeline(t_token_lst **token_lst, t_tree **pipeline)
{
	t_tree	*command;
	t_tree	*commands;

	commands = NULL;
	while ((*token_lst))
	{
		command = tree_get_command(token_lst);
		if (command == NULL)
		{
			free_tree(&commands);
			return (false);
		}
		tree_add_sibling_back(&commands, command);
		if ((*token_lst) && (*token_lst)->token.type == PIPE
			&& (*token_lst)->next)
			consume(token_lst);
		else
			break ;
	}
	*pipeline = tree_create_new(T_PIPELINE, NULL);
	tree_add_back(pipeline, commands);
	return (true);
}

t_tree	*tree_get_pipeline(t_token_lst **token_lst)
{
	t_tree	*pipeline;
	bool	check_err;

	pipeline = NULL;
	if ((*token_lst))
	{
		check_err = tree_set_pipeline(token_lst, &pipeline);
		if (!check_err)
			return (NULL);
	}
	return (pipeline);
}
