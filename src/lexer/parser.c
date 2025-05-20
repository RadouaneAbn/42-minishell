#include <parser.h>

bool	syntax_error(bool error)
{
	static bool	err;

	if (error)
		err = error;
	return (err);
}

void	get_subshell(t_token_lst	**token_lst)
{
		printf("[");
		while (*token_lst)
		{
			if ((*token_lst)->token->type == L_PAREN)
				get_subshell(&(*token_lst)->next);
			else if ((*token_lst)->token->type == R_PAREN)
			{
				*token_lst = (*token_lst)->next;
				printf("]\n");
				return ;
			}
			else
				printf("%s", (*token_lst)->token->lexeme);
			if (syntax_error(false))
				return ;
			*token_lst = (*token_lst)->next;

		}
		syntax_error(true);
		if (syntax_error(false))
			printf("error");
}


t_tree	tree_getcommand(t_token_lst **token_lst)
{
	
}

t_tree tree_getpipeline(t_token_lst **token_lst)
{
	t_tree	*command;
	t_tree	*pipeline;

	command = tree_getcommand(token_lst);
	pipeline = tree_getpipeline(token_lst);

	return ();
}

t_tree	tree_getcompound_command(t_token_lst **token_lst)
{
	t_tree	pipeline;

	pipeline = lstget_pipeline(token_lst);

	compound_command = lstget_compound_command(token_lst);	

	return ();
}

t_tree	*parser(t_token_lst *token_lst)
{
	return (lst_getcompound_command(token_lst));
	return (NULL);
}
