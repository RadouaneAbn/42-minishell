/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_get_compound_command.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:35:00 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/16 11:02:31 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_type	get_pipeline_relation(t_token_type	type)
{
	if (type == AND)
		return (T_AND);
	return (T_OR);
}

bool	tree_set_compound_command(t_token_lst **token_lst, t_tree **compound_command)
{
	t_tree	*pipelines;
	t_tree	*pipeline;
	t_tree	*pipeline_relation;

		pipelines = NULL;
		while ((*token_lst))
		{
			pipeline = tree_get_pipeline(token_lst);
			if (pipeline == NULL)
				return (free_tree(&pipelines), false);
			tree_add_sibling_back(&pipelines, pipeline);
			if ((*token_lst) && ((*token_lst)->token.type == AND
				|| (*token_lst)->token.type == OR) && (*token_lst)->next)
			{
				pipeline_relation = tree_create_new(get_pipeline_relation((*token_lst)->token.type), NULL);
				consume(token_lst);
			}
			else
				break ;
			tree_add_sibling_back(&pipelines, pipeline_relation);
		}
		*compound_command = tree_create_new(T_COMPOUND_COMMAND, NULL);
		tree_add_back(compound_command, pipelines);
		return (true);
}

t_tree	*tree_get_compound_command(t_token_lst **token_lst)
{
	t_tree	*compound_command;
	bool	check_err;

	compound_command = NULL;
	if ((*token_lst))
	{
		check_err = tree_set_compound_command(token_lst, &compound_command);
		if (!check_err)
			return (NULL);
	}
	return (compound_command);
}
