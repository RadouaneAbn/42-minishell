#include <minishell.h>

t_tree	*tree_get_compound_command(t_token_lst **token_lst)
{
	t_tree	*compound_command;
	t_tree	*pipelines;
	t_tree	*pipeline;

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
				consume(token_lst);
			else
				break ;
		}
		compound_command = tree_create_new(10, NULL);
		tree_add_back(&compound_command, pipelines);
	}
	return (compound_command);
}

t_tree *parser(t_token_lst **token_lst)
{
	t_tree *compound_command = tree_get_compound_command(token_lst);
	if (*token_lst)
	{
		printf("error [%s]\n", (*token_lst)->token->lexeme);
		return (NULL);
	}
	return (compound_command);
}
