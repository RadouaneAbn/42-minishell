#include <minishell.h>

t_tree	*tree_get_pipeline(t_token_lst **token_lst)
{
	t_tree	*pipeline;
	t_tree	*command;
	t_tree	*commands;

	pipeline = NULL;
	commands = NULL;
	if ((*token_lst))
	{
		pipeline = tree_create_new(9, NULL);
		while ((*token_lst))
		{
			command = tree_get_command(token_lst);
			tree_add_sibling_back(&commands, command);
			if ((*token_lst) && (*token_lst)->token->type == PIPE)
				consume(token_lst);
			else
				break ;
		}
		tree_add_back(&pipeline, commands);
	}
	return (pipeline);
}
