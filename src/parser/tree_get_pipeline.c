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
		while ((*token_lst))
		{
			command = tree_get_command(token_lst);
			if (command == NULL)
				return (NULL);
			tree_add_sibling_back(&commands, command);
			if ((*token_lst) && (*token_lst)->token->type == PIPE && (*token_lst)->next)
				consume(token_lst);
			else
				break ;
		}
		pipeline = tree_create_new(9, NULL);
		tree_add_back(&pipeline, commands);
	}
	return (pipeline);
}
