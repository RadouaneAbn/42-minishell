#include <minishell.h>

t_type	get_pipeline_relation(int	type)
{
	if (type == AND)
		return (T_AND);
	return (T_OR);
}

t_tree	*tree_get_compound_command(t_token_lst **token_lst)
{
	t_tree	*compound_command;
	t_tree	*pipelines;
	t_tree	*pipeline;
	t_tree	*pipeline_relation;

	compound_command = NULL;
	if ((*token_lst))
	{
		pipelines = NULL;
		while ((*token_lst))
		{
			pipeline = tree_get_pipeline(token_lst);
			if (pipeline == NULL)
				return (NULL);
			tree_add_sibling_back(&pipelines, pipeline);
			if ((*token_lst) && ((*token_lst)->token->type == AND || (*token_lst)->token->type == OR) && (*token_lst)->next)
			{
				pipeline_relation = tree_create_new(get_pipeline_relation((*token_lst)->token->type), NULL);
				consume(token_lst);
			}
			else
				break ;
			tree_add_sibling_back(&pipelines, pipeline_relation);
		}
		compound_command = tree_create_new(T_COMPOUND_COMMAND, NULL);
		tree_add_back(&compound_command, pipelines);
	}
	return (compound_command);
}

